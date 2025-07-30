#include "MockSSD.h"

void MockSSD::Write(int lba, const std::string& value) {
  storage[lba] = value;
}

std::string MockSSD::Read(int lba) {
  auto it = storage.find(lba);
  if (it != storage.end()) {
    return it->second;
  }
  return "0x00000000";
}