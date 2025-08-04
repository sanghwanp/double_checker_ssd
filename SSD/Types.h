#pragma once
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>

#include "SSDConfig.h"

using std::string;

enum CMD_TYPE { eWriteCmd, eReadCmd, eEraseCmd, eFlushCmd, eInvalidCmd };

inline bool IsDec(const string& str) {
  if (!(isdigit(str[0]) || str[0] == '-')) {
    return false;
  }

  for (char c : str.substr(1)) {
    if (!isdigit(c)) {
      return false;
    }
  }
  return true;
}

inline bool IsHex(const string& str) {
  if (str.size() < 3 || str.substr(0, 2) != "0x") return false;
  for (size_t i = 2; i < str.size(); ++i) {
    if (!isxdigit(str[i])) return false;
  }
  return true;
}

struct LBA {
  unsigned int val;
  LBA(unsigned int val) : val(val) {}
  static bool IsValid(const string& str) {
    if (str.empty()) return false;
    if (!IsDec(str)) return false;
    unsigned int val = std::stoul(str, nullptr, 0);
    return val < MAX_LBA_CNT;
  }

  static unsigned int Parse(const string& str) {
    return std::stoul(str, nullptr, 0);
  }
};

struct DATA {
  unsigned int val;
  DATA(unsigned int val) : val(val) {}

  static bool IsValid(const string& str) {
    if (!IsHex(str)) return false;

    unsigned long val = std::stoul(str, nullptr, 16);
    return val <= MAX_DATA_VALUE;
  }

  static unsigned int Parse(const string& str) {
    return std::stoul(str, nullptr, 16);
  }
};

struct SIZE_E {
  unsigned int val;
  SIZE_E(unsigned int val) : val(val) {}

  static bool IsValid(const string& str1, const string& str2) {
    if (str2.empty()) return false;
    if (!IsDec(str2)) return false;
    unsigned int val1 = std::stoul(str1, nullptr, 0);
    unsigned int val2 = std::stoul(str2, nullptr, 0);
    return (val1 + val2) <= MAX_LBA_CNT && val2 <= MAX_ERASE_SIZE;
  }

  static unsigned int Parse(const string& str) {
    return std::stoul(str, nullptr, 0);
  }
};
