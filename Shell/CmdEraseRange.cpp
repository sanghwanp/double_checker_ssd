#include "CmdEraseRange.h"

#include <iostream>

CommandEraseRange::CommandEraseRange(SSDInterface* ssdInterface)
    : ssd(ssdInterface) {}

bool CommandEraseRange::Call(const std::vector<std::string>& program) {
  // program example:
  // {"erase_range", "5", "20"}
  // {"erase_range", "60", "40"}
  // {"erase_range", "0", "99"}

  // precondition check
  if (program.size() != PROGRAM_SIZE) {
    // ERROR
    return false;
  }

  unsigned int lbaStart;
  unsigned int lbaEnd;
  try {
    lbaStart = std::stoi(program[LBA_START_INDEX]);
    lbaEnd = std::stoi(program[LBA_END_INDEX]);
  } catch (...) {
    // ERROR
    return false;
  }

  if (IsInvalidLBA(lbaStart) || IsInvalidLBA(lbaEnd)) {
    // ERROR
    return false;
  }

  if (lbaEnd < lbaStart) {
    unsigned int tmp = lbaEnd;
    lbaEnd = lbaStart;
    lbaStart = tmp;
  }

  while (lbaStart <= lbaEnd) {
    int size = lbaEnd - lbaStart + 1;
    int actualSize = (size > 10) ? 10 : size;

    ssd->Erase(lbaStart, actualSize);

    lbaStart += actualSize;
  }

  // SUCCESS
  std::cout << "[Eraserange] Done\n";
  return true;
}

bool CommandEraseRange::IsInvalidLBA(unsigned int lba) { return lba > MAX_LBA; }
