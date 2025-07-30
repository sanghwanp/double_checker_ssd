#include "MockSSD.h"
#include <stdexcept>

void MockSSD::Write(int lba, const string& value) {
  if (IsInvalidLBA(lba) || IsInvalidValue(value)) {
    return;
  }
  storage[lba] = value;
}

string MockSSD::Read(int lba) {
  if (IsInvalidLBA(lba)) {
    return "ERROR";
  }
  auto it = storage.find(lba);
  if (it != storage.end()) {
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
    bool is_digit = ('0' <= c && c <= '9');
    bool is_upper = ('A' <= c && c <= 'F');
    bool is_lower = ('a' <= c && c <= 'f');
    if (!(is_digit || is_upper || is_lower)) return true;
  }

  return false;
}