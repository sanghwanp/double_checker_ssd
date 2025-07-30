#pragma once
#include <string>
#include <vector>

#include "SSDInterface.h"

class CommandWrite {
 public:
  CommandWrite(SSDInterface* ssdInterface);
  bool Call(std::vector<std::string> program);

 private:
  bool IsInvalidLBA(int lba);
  bool IsInvalidValue(const string& value);
  void printInvalidCommandMessage();
  void printSuccessMessage();
  SSDInterface* ssd;

  const int COMMAND_INDEX = 0;
  const int LBA_INDEX = 1;
  const int VALUE_INDEX = 2;
  const std::string INVALID_COMMAND_MESSAGE = "INVALID COMMAND\n";
  const std::string SUCCESS_MESSAGE = "[Write] Done\n";
};