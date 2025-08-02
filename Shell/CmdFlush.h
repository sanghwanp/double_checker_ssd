#pragma once
#include <string>
#include <vector>

#include "SSDInterface.h"
#include "ICommand.h"

class CommandFlush : public IShellCommand {
 public:
  CommandFlush(SSDInterface* ssdInterface);
  bool Call(IParam& param);

 private:
  SSDInterface* ssd;
  const int COMMAND_SIZE = 1;
};
