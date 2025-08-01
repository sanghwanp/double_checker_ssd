#include "CommandBufferEntry.h"
using CmdType = CommandBufferConfig::CmdType;

CommandBufferEntry::CommandBufferEntry()
    : cmdType(CmdType::INVALID),
      startLba(CommandBufferConfig::NOT_AVAILABLE),
      endLba(CommandBufferConfig::NOT_AVAILABLE),
      data(0) {}
CommandBufferEntry::CommandBufferEntry(CmdType cmdType, unsigned int startLba,
                                       unsigned int endLba,
                                       unsigned long long data)
    : startLba(startLba), endLba(endLba), data(data), cmdType(cmdType) {
  Validator();
}

int CommandBufferEntry::Length() const { return endLba - startLba + 1; }

std::string CommandBufferEntry::ToString() const {
  std::string result;
  if (cmdType == CmdType::WRITE) {
    result = "W_";
  } else if (cmdType == CmdType::ERASE) {
    result = "E_";
  } else {
    throw std::invalid_argument("Invalid CmdType: " +
                                CommandBufferConfig::GetCmdTypeString(cmdType));
  }
  result += std::to_string(startLba) + "_" + std::to_string(endLba) + "_" +
            std::to_string(data);
  return result;
}

void CommandBufferEntry::Print() const {
  printf("[%d,%d]->val:%llu, cmdType:%s\n", startLba, endLba, data,
         CommandBufferConfig::GetCmdTypeString(cmdType).c_str());
}

CommandBufferEntry::CommandBufferEntry(unsigned int startLba,
                                       unsigned int endLba,
                                       unsigned long long data)
    : startLba(startLba), endLba(endLba), data(data) {
  if (data == 0) {
    cmdType = CmdType::ERASE;
  } else {
    cmdType = CmdType::WRITE;
  }

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

CommandBufferConfig::CmdType CommandBufferEntry::GetCmdType() const {
  return cmdType;
}

unsigned int CommandBufferEntry::GetStartLba() const { return startLba; }

unsigned int CommandBufferEntry::GetEndLba() const { return endLba; }

unsigned long long CommandBufferEntry::GetData() const { return data; }
