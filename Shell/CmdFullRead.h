#pragma once

#include <string>
#include <vector>

#include "SSDInterface.h"
#include "ICommand.h"

class CommandFullRead : public IShellCommand{
 public:
  CommandFullRead(SSDInterface* ssdInterface);
  bool Call(IParam& param);

 private:
  std::string static GenerateOutputStr(unsigned int lba, std::string value);

  SSDInterface* ssd;
  const char* COMMAND_NAME = "fullread";
  const int COMMAND_NAME_INDEX = 0;
  const int PROGRAM_SIZE = 1;
  const unsigned int MIN_LBA = 0;
  const unsigned int MAX_LBA = 99;
};
