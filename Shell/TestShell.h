#pragma once

#include "ICommand.h"
#include "Parser.h"
#include "SSDInterface.h"

class TestShell {
 public:
  TestShell(SSDInterface* ssdDriver);
  int Exec(void);

 private:
  int parseAndExecCommand(std ::string command);
  IShellCommand* GetCommand(IParam& param);
  IScriptCommand* GetScriptCommand(IParam& param);
  IParam& ParseCommand(std::string& command);
  Parser parser;

  SSDInterface* ssdDriver;
};
