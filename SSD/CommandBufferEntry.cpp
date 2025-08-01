#include "CommandBufferEntry.h"
using CmdType = CommandBufferConfig::CmdType;

CommandBufferEntry::CommandBufferEntry()
    : cmdType(CmdType::INVALID),
      startLba(CommandBufferConfig::NotAvailable),
      endLba(CommandBufferConfig::NotAvailable),
      data(0) {}
CommandBufferEntry::CommandBufferEntry(CmdType cmdType, unsigned int startLba,
                                       unsigned int endLba,
                                       unsigned long long data)
    : startLba(startLba), endLba(endLba), data(data), cmdType(cmdType) {
  Validator();
}

int CommandBufferEntry::Length() const { return endLba - startLba + 1; }

std::string CommandBufferEntry::ToString(CmdType cmdType) const {
  if (cmdType == CmdType::WRITE)
    return "WRITE";
  else if (cmdType == CmdType::ERASE)
    return "ERASE";
  else
    return "NOTHING";
}

void CommandBufferEntry::Print() const {
  printf("[%d,%d]->val:%llu, cmdType:%startLba\n", startLba, endLba, data,
         ToString(cmdType).c_str());
}

CommandBufferEntry::CommandBufferEntry(unsigned int startLba,
                                       unsigned int endLba,
                                       unsigned long long data)
    : startLba(startLba), endLba(endLba), data(data) {
  if (data == 0)
    cmdType = CmdType::ERASE;
  else
    cmdType = CmdType::WRITE;
  Validator();
}

void CommandBufferEntry::Validator() {
  if (cmdType == CmdType::WRITE) {
    if (startLba != endLba) {
      throw std::invalid_argument("if CmdType is WRITE -> startLba == endLba");
    }
  }

  if (cmdType == CmdType::ERASE) {
    if (data != 0) {
      throw std::invalid_argument("if CmdType is ERASE -> data == 0");
    }
  }

  if (data != 0) {
    if (cmdType != CmdType::WRITE) {
      throw std::invalid_argument("If data != 0 -> cmdType must be WRITE");
    }
  }
}
