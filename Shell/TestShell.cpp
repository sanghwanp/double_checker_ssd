#include "TestShell.h"

#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "CmdTestScript.h"
#include "ICommand.h"
#include "ICommandFactory.h"

int TestShell::Exec(void) {
  std::string command;

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

  IShellCommand* cmd = GetCommand(param);

  // execute the command
  if (cmd != nullptr) {
    ret = cmd->Call(param);
  } else if (param.eCmd == eScriptCmd) {
    result = GetScriptCommand(param)->Call(param);
    std::cout << result << std::endl;
  } else {
    std::cout << "INVALID COMMAND" << std::endl;
  }

  return param.eCmd;
}

IShellCommand* TestShell::GetCommand(IParam& param) {
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
