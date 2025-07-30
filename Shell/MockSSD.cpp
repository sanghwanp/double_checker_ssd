#include "MockSSD.h"

void MockSSD::Write(int lba, const std::string& value) {
  last_written_lba_ = lba;
  last_written_value_ = value;
}

std::string MockSSD::Read(int lba) {
  // PR1 green version: 테스트 통과를 위한 최소 구현
  if (lba == last_written_lba_) {
    return last_written_value_;
  }
  return "0x00000000";
}
