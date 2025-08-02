#include "TestShell.h"

#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "ICommand.h"

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
  IParam& param = *parser.Parse(command);
  bool ret = true;

  IShellCommand* cmd =
      ICommandFactory::GetInstance()->CreateCommand(param, ssdDriver);

  // execute the command
  if (cmd != nullptr) {
    ret = cmd->Call(param);
  }

  // post processing
  switch (param.eCmd) {
    case eScriptCmd: {
      CommandTestScript commandTestScript(ssdDriver);
      std::string result = commandTestScript.CallSciprt(param);
      std::cout << result << std::endl;
      break;
    }
    case eInvalidCmd: {
      std::cout << "INVALID COMMAND" << std::endl;
      break;
    }
  }
  return param.eCmd;
}
