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
  const char* COMMAND_NAME = "flush";
  const std::string INVALID_COMMAND_MESSAGE = "INVALID COMMAND\n";

  void printInvalidCommandMessage();
};