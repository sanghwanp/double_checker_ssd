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

  if (size >= 0) {
    ssd->Erase(lba, size);
  } else {
    int lbaStart = lba + size + 1;
    int sizeForward = -size;
    ssd->Erase(lbaStart, sizeForward);
  }

  // SUCCESS
  std::cout << "[Erase] Done\n";
  return true;
}

bool CommandErase::IsInvalidLBA(unsigned int lba) { return lba > MAX_LBA; }
