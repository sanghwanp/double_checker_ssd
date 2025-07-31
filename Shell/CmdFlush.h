#pragma once
#include <string>
#include <vector>

#include "SSDInterface.h"

class CommandFlush {
 public:
  CommandFlush(SSDInterface* ssdInterface);
  bool Call(const std::vector<std::string>& tokens);

 private:
  SSDInterface* ssd;
  const int COMMAND_SIZE = 1;
  const std::string INVALID_COMMAND_MESSAGE = "INVALID COMMAND\n";

  void printInvalidCommandMessage();
};