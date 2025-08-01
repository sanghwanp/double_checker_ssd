#include "CmdWrite.h"

#include <iostream>
#include <string>

CommandWrite::CommandWrite(SSDInterface* ssdInterface) : ssd(ssdInterface) {}

bool CommandWrite::Call(IParam& param) {
  if (param.eCmd == eInvalidCmd) return false;
  WriteParam& writeParam = dynamic_cast<WriteParam&>(param);

  int lba = std::stoi(writeParam.lba);

  const std::string& value = writeParam.data;

  if (IsInvalidLBA(lba) || IsInvalidValue(value)) {

    return false;
  }

  ssd->Write(lba, value);
  printSuccessMessage();
  return true;
}

bool CommandWrite::IsInvalidLBA(int lba) { return lba < 0 || lba >= 100; }

bool CommandWrite::IsInvalidValue(const string& value) {
  if (value.size() != 10) return true;
  if (value[0] != '0' || value[1] != 'x') return true;

  for (int i = 2; i < 10; ++i) {
    char c = value[i];

    bool isDigit = ('0' <= c && c <= '9');
    bool isUpper = ('A' <= c && c <= 'F');
    bool isLower = ('a' <= c && c <= 'f');
    if (!(isDigit || isUpper || isLower)) return true;
  }

  return false;
}

void CommandWrite::printInvalidCommandMessage() {
  std::cout << INVALID_COMMAND_MESSAGE;
}

void CommandWrite::printSuccessMessage() {
  std::cout << SUCCESS_MESSAGE;
}
