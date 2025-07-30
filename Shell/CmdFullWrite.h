#pragma once
#include <string>
#include <vector>

#include "SSDInterface.h"

class CommandFullWrite {
 public:
  CommandFullWrite(SSDInterface* ssdInterface);
  bool Call(const std::vector<std::string> program);

 private:
  bool IsInvalidValue(const string& value);
  void printInvalidCommandMessage();
  void printSuccessMessage();
  SSDInterface* ssd;

  const int COMMAND_INDEX = 0;
  const int VALUE_INDEX = 1;
  const std::string INVALID_COMMAND_MESSAGE = "INVALID COMMAND\n";
  const std::string SUCCESS_MESSAGE = "[Fullwrite] Done\n";
};