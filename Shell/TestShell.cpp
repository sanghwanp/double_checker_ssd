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
  IParam& parsedCommand = *parser.Parse(command);
  bool ret = true;

  IShellCommand* cmd =
      ICommandFactory::GetInstance()->CreateCommand(parsedCommand, ssdDriver);

  // execute the command
  if (cmd != nullptr) {
    ret = cmd->Call(parsedCommand);
  }

  // post processing
  switch (parsedCommand.eCmd) {
    case eScriptCmd: {
      ScriptParam* scriptCmd = dynamic_cast<ScriptParam*>(parsedCommand);
      std::string result = commandTestScript.CallSciprt(*parsedCommand);
      std::cout << result << std::endl;
      break;
    }
    case eInvalidCmd: {
        std::cout << "INVALID COMMAND" << std::endl;
        break;
    }
  }
  return parsedCommand.eCmd;
}
