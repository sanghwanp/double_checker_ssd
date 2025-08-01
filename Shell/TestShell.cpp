#include "TestShell.h"

#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

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
  IParam* parsedCommand = parser.Parse(command);
  int eCmd = parsedCommand->eCmd;

  switch (eCmd) {
    case eWriteCmd: {
      WriteParam* writeCmd = dynamic_cast<WriteParam*>(parsedCommand);
      std::vector<std::string> program = {"write", writeCmd->lba,
                                          writeCmd->data};
      commandWrite.Call(program);
      break;
    }
    case eReadCmd: {
      ReadParam* readCmd = dynamic_cast<ReadParam*>(parsedCommand);
      std::vector<std::string> program = {"read", readCmd->lba};
      commandRead.Call(program);
      break;
    }
    case eHelpCmd: {
      std::vector<std::string> program = {"help"};
      commandHelp.Call(program);
      break;
    }
    case eExitCmd: {
      std::vector<std::string> program = {"exit"};
      commandExit.Call(program);
      break;
    }
    case eFullwrite: {
      FullWriteParam* fwCmd = dynamic_cast<FullWriteParam*>(parsedCommand);
      std::vector<std::string> program = {"fullwrite", fwCmd->data};
      commandFullWrite.Call(program);
      break;
    }
    case eFullread: {
      std::vector<std::string> program = {"fullread"};
      commandFullRead.Call(program);
      break;
    }
    case eEraseCmd: {
      EraseParam* eraseCmd = dynamic_cast<EraseParam*>(parsedCommand);
      std::vector<std::string> program = {"erase", eraseCmd->lba, eraseCmd->size};
      commandErase.Call(program);
      break;
    }
    case eFlushCmd: {
      std::vector<std::string> program = {"flush"};
      commandFlush.Call(program);
      break;
    }
    case eScriptCmd: {
      ScriptParam* scriptCmd = dynamic_cast<ScriptParam*>(parsedCommand);
      if (commandTestScript.Call(*parsedCommand)) {
        ITestScriptCase::PrintPassResult();
      } else {
        ITestScriptCase::PrintFailResult();
      }
      break;
    }
    case eInvalidCmd:
    default: {
      std::cout << "INVALID COMMAND" << std::endl;
      break;
    }
  }
  return eCmd;
}
