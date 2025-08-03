#include "CommandBufferEntry.h"
#include "Types.h"

CommandBufferEntry::CommandBufferEntry()
    : cmdType(CMD_TYPE::eInvalidCmd),
      startLba(CommandBufferConfig::NOT_AVAILABLE),
      endLba(CommandBufferConfig::NOT_AVAILABLE),
      data(0) {}
CommandBufferEntry::CommandBufferEntry(CMD_TYPE cmdType, unsigned int startLba,
                                       unsigned int endLba,
                                       unsigned long long data)
    : startLba(startLba), endLba(endLba), data(data), cmdType(cmdType) {
  Validator();
}

int CommandBufferEntry::Length() const { return endLba - startLba + 1; }

std::string CommandBufferEntry::ToString() const {
  std::string result;
  if (cmdType == eWriteCmd) {
    result = "W_" + std::to_string(startLba) + "_" + std::to_string(endLba) + "_" +
        std::to_string(data);
  } else if (cmdType == eEraseCmd) {
      result = "E_" + std::to_string(startLba) + "_" + std::to_string(endLba);
  } else {
    result = "empty";
    return result;
  }
  return result;
}

std::string CommandBufferEntry::ToString(CMD_TYPE cmdType) const {
  if (cmdType == eWriteCmd)
    return "WRITE";
  else if (cmdType == eEraseCmd)
    return "ERASE";
  else
    return "NOTHING";
}

void CommandBufferEntry::Print() const {
  printf("[%d,%d]->val:%llu, cmdType:%s\n", startLba, endLba, data,
         ToString(cmdType).c_str());
}

CommandBufferEntry::CommandBufferEntry(unsigned int startLba,
                                       unsigned int endLba,
                                       unsigned long long data)
    : startLba(startLba), endLba(endLba), data(data) {
  if (data == 0)
    cmdType = eEraseCmd;
  else
    cmdType = eWriteCmd;
  Validator();
}

void CommandBufferEntry::Validator() {
  if (cmdType == eWriteCmd) {
    if (startLba != endLba) {
      throw std::invalid_argument("if CMD_TYPE is WRITE -> startLba == endLba");
    }
  }

  if (cmdType == eEraseCmd) {
    if (data != 0) {
      throw std::invalid_argument("if CMD_TYPE is ERASE -> data == 0");
    }
  }

  if (data != 0) {
    if (cmdType != eWriteCmd) {
      throw std::invalid_argument("If data != 0 -> cmdType must be WRITE");
    }
  }
}
