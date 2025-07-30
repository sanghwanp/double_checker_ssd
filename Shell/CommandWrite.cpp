#include "CommandWrite.h"

#include <iostream>

int CommandWrite(SSDInterface& ssd, const std::vector<std::string>& tokens) {
  if (tokens.size() != 3) {
    std::cout << "ERROR\n";
    return -1;
  }

  int lba;
  try {
    lba = std::stoi(tokens[1]);
  } catch (...) {
    std::cout << "ERROR\n";
    return -1;
  }

  const std::string& value = tokens[2];

  if (IsInvalidLBA(lba) || IsInvalidValue(value)) {
    std::cout << "ERROR\n";
    return -1;
  }

  ssd.Write(lba, value);
  std::cout << "[Write] Done\n";
  return 0;
}

bool IsInvalidLBA(int lba) { return lba < 0 || lba >= 100; }

bool IsInvalidValue(const string& value) {
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