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

void MockSSD::Flush() {
  // No-op: MockSSD applies writes directly to its cache,
  // so there is no buffered data that needs flushing.
}
