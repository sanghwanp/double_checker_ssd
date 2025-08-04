#include "CommandBufferHandler.h"

#include "Types.h"

using std::vector;

vector<CommandBufferEntry> CommandBufferHandler::AddWrite(unsigned int lba,
                                                          unsigned int data) {
  CommandBufferEntry newCmd(eWriteCmd, lba, lba,
                            static_cast<unsigned long long>(data));

  vector<CommandBufferEntry> savedCmds = commandBuffer.LoadCmdsFromBuffer();
  commandBuffer.FlushBuffer(false);
  if (IsFullCmds(savedCmds)) {  // Buffer가 꽉 찬 경우
    commandBuffer.WriteCmdsToBuffer({newCmd});
    return savedCmds;
  }

  // 일반적인 Case
  savedCmds.push_back(newCmd);
  vector<CommandBufferEntry> optimizedCmds =
      commandBufferOptimizer.Optimize(savedCmds);
  commandBuffer.WriteCmdsToBuffer(optimizedCmds);
  return {};
}

vector<CommandBufferEntry> CommandBufferHandler::AddErase(unsigned int lba,
                                                          int delta) {
  validateEraseDelta(delta);
  const int startLba = GetStartLba(lba, delta);
  const int endLba = GetEndLba(lba, delta);
  validateEraseLba(startLba, endLba);
  CommandBufferEntry newCmd(eEraseCmd, startLba, endLba, 0ULL);

  vector<CommandBufferEntry> savedCmds = commandBuffer.LoadCmdsFromBuffer();
  commandBuffer.FlushBuffer(false);
  if (IsFullCmds(savedCmds)) {  // Buffer가 꽉 찬 경우
    commandBuffer.WriteCmdsToBuffer({newCmd});
    return savedCmds;
  }

  // 일반적인 Case
  savedCmds.push_back(newCmd);
  vector<CommandBufferEntry> optimizedCmds =
      commandBufferOptimizer.Optimize(savedCmds);
  commandBuffer.WriteCmdsToBuffer(optimizedCmds);
  return {};
}

bool CommandBufferHandler::TryFastRead(unsigned int lba,
                                       unsigned int &out_value) const {
  vector<CommandBufferEntry> savedCmds = commandBuffer.LoadCmdsFromBuffer();
  for (int i = savedCmds.size() - 1; i >= 0; i--) {
    const CommandBufferEntry &cmdEntry = savedCmds[i];
    if (cmdEntry.startLba <= lba && lba <= cmdEntry.endLba) {
      out_value = static_cast<unsigned int>(cmdEntry.data);
      return true;
    }
  }
  return false;
}

std::vector<CommandBufferEntry> CommandBufferHandler::Flush() {
  vector<CommandBufferEntry> savedCmds = commandBuffer.LoadCmdsFromBuffer();
  commandBuffer.FlushBuffer(true);
  return savedCmds;
}

bool CommandBufferHandler::IsBufferFull() {
  vector<CommandBufferEntry> savedCmds = commandBuffer.LoadCmdsFromBuffer();
  return IsFullCmds(savedCmds);
}

bool CommandBufferHandler::IsFullCmds(
    std::vector<CommandBufferEntry> &savedCmds) const {
  return savedCmds.size() >= CommandBufferConfig::MAX_BUFFER;
}

int CommandBufferHandler::GetStartLba(int lba, int delta) const {
  if (delta < 0) {
    return lba + delta + 1;
  }

  return lba;
}
int CommandBufferHandler::GetEndLba(int lba, int delta) const {
  if (delta < 0) {
    return lba;
  }

  return lba + delta - 1;
}

void CommandBufferHandler::validateEraseDelta(int delta) {
  if (delta == 0) {
    throw std::invalid_argument(
        "At AddErase(lba, delta), 'delta' must not be 0.");
  }
  if (abs(delta) > CommandBufferConfig::LBA_ERASE_RANGE_LIMIT) {
    throw std::invalid_argument(
        "Erase range must be less than or equal to " +
        std::to_string(CommandBufferConfig::LBA_ERASE_RANGE_LIMIT));
  }
}

void CommandBufferHandler::validateEraseLba(int startLba, int endLba) {
  if (startLba < CommandBufferConfig::MIN_LBA ||
      startLba > CommandBufferConfig::MAX_LBA) {
    throw std::invalid_argument("invalid startLba: " +
                                std::to_string(startLba));
  }
  if (endLba < CommandBufferConfig::MIN_LBA ||
      endLba > CommandBufferConfig::MAX_LBA) {
    throw std::invalid_argument("invalid endLba: " + std::to_string(endLba));
  }
  const int LBA_RANGE_SIZE = endLba - startLba + 1;
  if (LBA_RANGE_SIZE > CommandBufferConfig::LBA_ERASE_RANGE_LIMIT) {
    throw std::invalid_argument("invalid lbaRangeSize: " +
                                std::to_string(LBA_RANGE_SIZE));
  }
}
