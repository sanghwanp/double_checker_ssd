#include "MockSSD.h"

void MockSSD::Write(int lba, const string& value) {
  if (IsInvalidLBA(lba) || IsInvalidValue(value)) {
    return;
  }
  cache[lba] = value;
}

string MockSSD::Read(int lba) {
  if (IsInvalidLBA(lba)) {
    return "ERROR";
  }
  auto it = cache.find(lba);
  if (it != cache.end()) {
    return it->second;
  }
  return "0x00000000";
}

bool MockSSD::IsInvalidLBA(int lba) { return lba < 0 || lba >= 100; }

bool MockSSD::IsInvalidValue(const string& value) {
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