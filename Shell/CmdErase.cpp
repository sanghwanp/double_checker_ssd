#include "CmdErase.h"

#include <algorithm>
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
  int sizeForward = GetForwardSize(lba, size);

  ExecuteErase(lbaForward, sizeForward);

  // SUCCESS
  std::cout << "[Erase] Done\n";
  return true;
}

bool CommandErase::IsInvalidLBA(unsigned int lba) { return lba > MAX_LBA; }

unsigned int CommandErase::GetForwardLBA(unsigned int lba, int size) {
  if (size >= 0) {
    return lba;
  }

  // size < 0
  int lbaStart = lba + size + 1;

  // need to return a valid lba
  // if lbaStart < 0, then we push it back up to 0
  return std::max(lbaStart, 0);
}

int CommandErase::GetForwardSize(unsigned int lba, int size) {
  if (size >= 0) {
    return size;
  }

  // re-calculate `size` by computing the size of [lbaForward ~ lba]
  unsigned int lbaForward = GetForwardLBA(lba, size);
  int sizeForward = lba - lbaForward + 1;
  return sizeForward;
}

void CommandErase::ExecuteErase(unsigned int lba, int size) {
  // this function assumes size >= 0
  unsigned int lbaCurr = lba;
  int remainingSize = size;

  while (lbaCurr <= MAX_LBA && remainingSize > 0) {
    // one ssd->Erase() call per one iteration

    int cappedSize = std::min(remainingSize, SSD_ERASE_MAX_SIZE);

    int actualSize;
    if (lbaCurr + cappedSize > MAX_LBA + 1) {
      actualSize = MAX_LBA - lbaCurr + 1;
    } else {
      actualSize = cappedSize;
    }

    ssd->Erase(lbaCurr, actualSize);

    lbaCurr += actualSize;
    remainingSize -= actualSize;
  }
}
