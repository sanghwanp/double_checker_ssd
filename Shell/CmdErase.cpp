#include "CmdErase.h"

#include <algorithm>
#include <iostream>

CommandErase::CommandErase(SSDInterface* ssdInterface) : ssd(ssdInterface) {}

bool CommandErase::Call(IParam& param) {
  EraseParam* eraseParam = dynamic_cast<EraseParam*>(&param);

  unsigned int lba;
  int size;
  try {
    lba = std::stoi(eraseParam->lba);
    size = std::stoi(eraseParam->size);
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

  // initialization
  unsigned int lbaCurr = lba;
  int remainingSize = size;

  while (IsValidErase(lbaCurr, remainingSize)) {
    // one ssd->Erase() call per one iteration

    // calibrate the erase size
    int actualSize = GetActualEraseSize(lbaCurr, remainingSize);

    ssd->Erase(lbaCurr, actualSize);

    updateLbaAndSize(lbaCurr, remainingSize, actualSize);
  }
}

bool CommandErase::IsValidErase(unsigned int lbaCurr, int remainingSize) {
  return lbaCurr <= MAX_LBA && remainingSize > 0;
}

int CommandErase::GetActualEraseSize(unsigned int lbaCurr, int remainingSize) {
  int cappedSize = std::min(remainingSize, SSD_ERASE_MAX_SIZE);

  if (lbaCurr + cappedSize > MAX_LBA + 1) {
    return MAX_LBA - lbaCurr + 1;
  } else {
    return cappedSize;
  }
}

void CommandErase::updateLbaAndSize(unsigned int& lbaCurr, int& remainingSize,
                                    int actualSize) {
  lbaCurr += actualSize;
  remainingSize -= actualSize;
}
