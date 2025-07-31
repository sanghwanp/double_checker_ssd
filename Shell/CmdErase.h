#pragma once

#include <string>
#include <vector>

#include "SSDInterface.h"

class CommandErase {
 public:
  CommandErase(SSDInterface* ssdInterface);
  bool Call(const std::vector<std::string>& program);

 private:
  bool IsInvalidLBA(unsigned int lba);

  SSDInterface* ssd;
  const int LBA_INDEX = 1;
  const int SIZE_INDEX = 2;
  const int PROGRAM_SIZE = 3;
  const unsigned int MAX_LBA = 99;
};
