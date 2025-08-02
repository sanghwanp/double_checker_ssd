#include "TestShell.h"

#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "CmdTestScript.h"
#include "ICommand.h"
#include "ICommandFactory.h"
#include "ILogger.h"

TestShell::TestShell(SSDInterface* ssdDriver) : ssdDriver(ssdDriver) {
  ILogger::GetInstance()->LogPrint("TestShell::TestShell",
                                   ssdDriver->GetName() + "is loaded", false);
}
int TestShell::Exec(void) {
  std::string command;
  ILogger::GetInstance()->LogPrint("TestShell::Exec", "Shell is starting", false);
  while (true) {
    std::cout << "Shell> ";
    std::getline(std::cin, command);

    int eCmd = parseAndExecCommand(command);
    if (eCmd == eExitCmd) break;
  }
  return 0;
}

int TestShell::parseAndExecCommand(std::string command) {
  bool ret = true;
  std::string result;

  IParam& param = ParseCommand(command);

  // execute the command
  if (param.eCmd == eScriptCmd) {
    result = GetScriptCommand(param)->Call(param);
    std::cout << result << std::endl;
  } else if (param.eCmd == eInvalidCmd) {
    ret = false;
  } else {
    IShellCommand* cmd = GetCommand(param);
    ret = cmd->Call(param);
  }

  if (ret == false) {
    std::cout << "INVALID COMMAND" << std::endl;
  }

  return param.eCmd;
}

IShellCommand* TestShell::GetCommand(IParam& param) {
  if (param.eCmd == eInvalidCmd) return nullptr;
  return ICommandFactory::GetInstance()->CreateCommand(param, ssdDriver);
}

IScriptCommand* TestShell::GetScriptCommand(IParam& param) {
  if (param.eCmd == eScriptCmd) {
    return new CommandTestScript{ssdDriver};
  }
  return nullptr;
}

IParam& TestShell::ParseCommand(std::string& command) {
  return *parser.Parse(command);
}
