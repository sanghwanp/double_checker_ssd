#pragma once

#include <string>
#include <vector>

#include "SSDInterface.h"
#include "ICommand.h"

class CommandRead :public IShellCommand{
 public:
  CommandRead(SSDInterface* ssdInterface);
  bool Call(IParam& param);

 private:
  bool IsInvalidLBA(unsigned int lba);

  SSDInterface* ssd;
  const int LBA_INDEX = 1;
  const int PROGRAM_SIZE = 2;
  const unsigned int MAX_LBA = 99;
};
