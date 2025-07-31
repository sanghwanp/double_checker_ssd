#pragma once

#include <string>
#include <vector>

#include "SSDInterface.h"

class CommandErase {
 public:
  CommandErase(SSDInterface* ssdInterface);
  bool Call(const std::vector<std::string>& program);

 private:
  unsigned int GetForwardLBA(unsigned int lba, int size);
  int GetForwardSize(unsigned int lba, int size);

  // erase algorithm related functions
  void ExecuteErase(unsigned int lba, int size);
  bool IsValidErase(unsigned int lbaCurr, int remainingSize);
  int GetActualEraseSize(unsigned int lbaCurr, int cappedSize);
  void updateLbaAndSize(unsigned int& lbaCurr, int& remainingSize,
                        int actualSize);

  const int LBA_INDEX = 1;
  const int SIZE_INDEX = 2;
  const int PROGRAM_SIZE = 3;
  const int SSD_ERASE_MAX_SIZE = 10;

 protected:
  bool IsInvalidLBA(unsigned int lba);

  SSDInterface* ssd;
  const unsigned int MAX_LBA = 99;
};
