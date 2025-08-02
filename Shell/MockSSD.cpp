#include "MockSSD.h"
#include "ILogger.h"

void MockSSD::Write(int lba, const string& value) {
  if (IsInvalidLBA(lba) || IsInvalidValue(value)) {
    return;
  }
  ILogger::GetInstance()->LogPrint("MockSSD::Write",
                                   "lba: " + std::to_string(lba) + ", value :" + value, false);

  cache[lba] = value;
}

string MockSSD::Read(int lba) {
  if (IsInvalidLBA(lba)) {
    return "ERROR";
  }
  auto it = cache.find(lba);
  if (it != cache.end()) {
    ILogger::GetInstance()->LogPrint(
        "MockSSD::Read",
        "lba: " + std::to_string(lba) + ", value :" + it->second,
        false);

    return it->second;
  }
  return "0x00000000";
}

void MockSSD::Erase(int lba, int size) {
  if (IsInvalidLBA(lba) || IsInvalidErase(lba, size)) {
    return;
  }

  int lbaEnd = lba + size - 1;
  ILogger::GetInstance()->LogPrint(
      "MockSSD::Erase",
      "lba: " + std::to_string(lba) + " ~ " + std::to_string(lbaEnd),
      false);
  for (int lbaIndex = lba; lbaIndex <= lbaEnd; lbaIndex++) {
    cache.erase(lbaIndex);
  }
}

void MockSSD::Flush() {
  ILogger::GetInstance()->LogPrint(
      "MockSSD::Flush", "Flush called", false);
  // No-op: MockSSD applies writes directly to its cache,
  // so there is no buffered data that needs flushing.
}
