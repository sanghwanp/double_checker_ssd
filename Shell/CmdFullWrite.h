#pragma once
#include <string>
#include <vector>

#include "SSDInterface.h"
#include "ICommand.h"

class CommandFullWrite : public IShellCommand {
 public:
  CommandFullWrite(SSDInterface* ssdInterface);
  bool Call(IParam& param) override;

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
