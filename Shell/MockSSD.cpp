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

void MockSSD::Erase(int lba, int size) {
  if (IsInvalidLBA(lba) || IsInvalidErase(lba, size)) {
    return;
  }

  int lbaEnd = lba + size - 1;
  for (int lbaIndex = lba; lbaIndex <= lbaEnd; lbaIndex++) {
    cache.erase(lbaIndex);
  }
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

bool MockSSD::IsInvalidErase(int lba, int size) {
  if (size < 0 || size > 10) {
    return true;
  }

  if (size == 0) {
    return false;
  }

  // assume lba is valid
  int lbaEnd = lba + size - 1;
  return lbaEnd >= 100;
}
