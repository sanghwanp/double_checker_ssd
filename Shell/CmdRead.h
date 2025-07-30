#pragma once

#include <string>
#include <vector>

#include "SSDInterface.h"

class CommandRead {
 public:
  CommandRead(SSDInterface* ssdInterface);
  bool Call(const std::vector<std::string>& program);

 private:
  bool IsInvalidLBA(unsigned int lba);

  SSDInterface* ssd;
  const int LBA_INDEX = 1;
  const int PROGRAM_SIZE = 2;
  const unsigned int MAX_LBA = 99;
};
