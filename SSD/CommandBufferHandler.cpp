#include "CommandBufferHandler.h"

using CmdType = CommandBufferConfig::CmdType;

void CommandBufferHandler::AddWrite(unsigned int lba, unsigned int data) {
  CommandBufferEntry cmdBufferEntry(CmdType::WRITE, lba, lba,
                                    static_cast<unsigned long long>(data));

}

void CommandBufferHandler::AddErase(unsigned int lba, int delta) {
  const int startLba = GetStartLba(lba, delta);
  const int endLba = GetEndLba(lba, delta);
  CommandBufferEntry cmdBufferEntry(CmdType::ERASE, startLba, endLba, 0ULL);
}

 bool CommandBufferHandler::TryFastRead(unsigned int lba,
                                       unsigned int& out_value) {
    return false;
}

std::vector<CommandBufferEntry> CommandBufferHandler::Flush() {
  return std::vector<CommandBufferEntry>();
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
