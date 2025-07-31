#include "CmdErase.h"

#include <iostream>

CommandErase::CommandErase(SSDInterface* ssdInterface) : ssd(ssdInterface) {}

bool CommandErase::Call(const std::vector<std::string>& program) {
  // program example:
  // {"erase", "5", "20"}
  // {"erase", "60", "-200"}
  // {"erase", "99", "0"}

  // precondition check
  if (program.size() != PROGRAM_SIZE) {
    // ERROR
    return false;
  }

  unsigned int lba;
  int size;
  try {
    lba = std::stoi(program[LBA_INDEX]);
    size = std::stoi(program[SIZE_INDEX]);
  } catch (...) {
    // ERROR
    return false;
  }

  if (IsInvalidLBA(lba)) {
    // ERROR
    return false;
  }

  // in case size < 0, convert lba & size to go forwards (lba 0 --> 99)
  unsigned int lbaForward = GetForwardLBA(lba, size);
  int sizeForward = GetForwardSize(size);

  ssd->Erase(lbaForward, sizeForward);

  // SUCCESS
  std::cout << "[Erase] Done\n";
  return true;
}

bool CommandErase::IsInvalidLBA(unsigned int lba) { return lba > MAX_LBA; }

unsigned int CommandErase::GetForwardLBA(unsigned int lba, int size) {
  if (size < 0) {
    return lba + size + 1;
  } else {
    return lba;
  }
}

int CommandErase::GetForwardSize(int size) {
  if (size < 0) {
    return -size;
  } else {
    return size;
  }
}
