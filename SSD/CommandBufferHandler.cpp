#include "CommandBufferHandler.h"
#include "Types.h"

using std::vector;

vector<CommandBufferEntry> CommandBufferHandler::AddWrite(unsigned int lba,
                                                          unsigned int data) {
  CommandBufferEntry newCmd(eWriteCmd, lba, lba,
                                    static_cast<unsigned long long>(data));

  vector<CommandBufferEntry> savedCmds = commandBuffer.LoadCmdsFromBuffer();
  commandBuffer.FlushBuffer();
  if (IsFullCmds(savedCmds)) {  // Buffer가 꽉 찬 경우
    commandBuffer.WriteCmdsToBuffer({ newCmd });
    return savedCmds;
  } else {  // 일반적인 Case
    savedCmds.push_back(newCmd);
    vector<CommandBufferEntry> optimizedCmds =
        commandBufferOptimizer.Optimize(savedCmds);
    commandBuffer.WriteCmdsToBuffer(optimizedCmds);
    return {};
  }
}

bool CommandBufferHandler::CheckBufferFull() {
  vector<CommandBufferEntry> savedCmds = commandBuffer.LoadCmdsFromBuffer();
  return savedCmds.size() >= CommandBufferConfig::MAX_BUFFER;
}

bool CommandBufferHandler::IsFullCmds(std::vector<CommandBufferEntry> &savedCmds) {
  return savedCmds.size() >= CommandBufferConfig::MAX_BUFFER;
}

vector<CommandBufferEntry> CommandBufferHandler::AddErase(unsigned int lba,
                                                          int delta) {
  const int startLba = GetStartLba(lba, delta);
  const int endLba = GetEndLba(lba, delta);
  CommandBufferEntry newCmd(eEraseCmd, startLba, endLba, 0ULL);

  vector<CommandBufferEntry> savedCmds = commandBuffer.LoadCmdsFromBuffer();
  commandBuffer.FlushBuffer();
  if (IsFullCmds(savedCmds)) {  // Buffer가 꽉 찬 경우
    commandBuffer.WriteCmdsToBuffer({newCmd});
    return savedCmds;
  } else {  // 일반적인 Case
    savedCmds.push_back(newCmd);
    vector<CommandBufferEntry> optimizedCmds =
        commandBufferOptimizer.Optimize(savedCmds);
    commandBuffer.WriteCmdsToBuffer(optimizedCmds);
    return {};
  }
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
  out_value = static_cast<unsigned int>(CommandBufferConfig::NOT_AVAILABLE);
  return false;
}

std::vector<CommandBufferEntry> CommandBufferHandler::Flush() {
  vector<CommandBufferEntry> savedCmds = commandBuffer.LoadCmdsFromBuffer();
  commandBuffer.FlushBuffer();
  return savedCmds;
}

int CommandBufferHandler::GetStartLba(int lba, int delta) const {
  if (delta < 0)
    return lba + delta + 1;
  else
    return lba;
}
int CommandBufferHandler::GetEndLba(int lba, int delta) const {
  if (delta < 0)
    return lba;
  else
    return lba + delta - 1;
}
