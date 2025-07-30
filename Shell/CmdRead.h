#pragma once

#include <string>
#include <vector>

#include "SSDInterface.h"

class CommandRead {
 public:
  CommandRead(SSDInterface* ssdInterface);
  bool Call(std::vector<std::string> program);

 private:
  bool IsInvalidLBA(int lba);

  SSDInterface* ssd;
  const int LBA_INDEX = 1;
  const int PROGRAM_SIZE = 2;
  const int MIN_LBA = 0;
  const int MAX_LBA = 99;
};
