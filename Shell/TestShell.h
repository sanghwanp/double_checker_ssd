#pragma once

#include "ICommand.h"
#include "Parser.h"
#include "CmdWrite.h"
#include "CmdRead.h"
#include "CmdFullWrite.h"
#include "CmdFullRead.h"
#include "CmdExit.h"
#include "CmdHelp.h"
#include "CmdErase.h"
#include "CmdEraseRange.h"
#include "CmdFlush.h"
#include "CmdTestScript.h"
#include "SSDInterface.h"

class TestShell {
 public:
  TestShell(SSDInterface* ssdDriver) : ssdDriver(ssdDriver) {}
  int Exec(void);

 private:
  int parseAndExecCommand(std ::string command);
  IShellCommand* GetCommand(IParam& param);
  IScriptCommand* GetScriptCommand(IParam& param);
  IParam& ParseCommand(std::string& command);
  Parser parser;

  SSDInterface* ssdDriver;
};
