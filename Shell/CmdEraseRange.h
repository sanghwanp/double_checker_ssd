#pragma once

#include <string>
#include <vector>

#include "SSDInterface.h"

class CommandEraseRange {
 public:
  CommandEraseRange(SSDInterface* ssdInterface);
  bool Call(const std::vector<std::string>& program);

 private:
  bool IsInvalidLBA(unsigned int lba);

  SSDInterface* ssd;
  const int LBA_START_INDEX = 1;
  const int LBA_END_INDEX = 2;
  const int PROGRAM_SIZE = 3;
  const unsigned int MAX_LBA = 99;
};
