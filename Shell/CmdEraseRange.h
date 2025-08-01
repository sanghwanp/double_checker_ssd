#pragma once

#include <string>
#include <vector>

#include "CmdErase.h"
#include "SSDInterface.h"

class CommandEraseRange : public CommandErase {
 public:
  CommandEraseRange(SSDInterface* ssdInterface);
  bool Call(IParam& param) override;

 private:
  const int LBA_START_INDEX = 1;
  const int LBA_END_INDEX = 2;
  const int PROGRAM_SIZE = 3;
};
