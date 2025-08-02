#pragma once
#include "CmdFullWrite.h"

#include <iostream>
#include <string>
#include <vector>

#include "SSDInterface.h"

CommandFullWrite::CommandFullWrite(SSDInterface* ssdInterface)
    : ssd(ssdInterface) {}

bool CommandFullWrite::Call(IParam& param) {
  if (param.eCmd == eInvalidCmd) return false;

  FullWriteParam* writeFullParam = dynamic_cast<FullWriteParam*>(&param);

  const std::string& value = writeFullParam->data;
  if (IsInvalidValue(value)) {
    return false;
  }

  for (unsigned lba = 0; lba < 100; ++lba) {
    ssd->Write(lba, value);
  }
  printSuccessMessage();
  return true;
}

bool CommandFullWrite::IsInvalidValue(const std::string& value) {
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

void CommandFullWrite::printInvalidCommandMessage() {
  std::cout << INVALID_COMMAND_MESSAGE;
}

void CommandFullWrite::printSuccessMessage() { std::cout << SUCCESS_MESSAGE; }
