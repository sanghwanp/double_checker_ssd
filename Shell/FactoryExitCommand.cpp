#include "CmdExit.h"
#include "CommandFactoryRegisterer.h"
#include "FactoryExitCommand.h"
#include "IParam.h"

IShellCommand* FactoryExitCommand::CreateCommand(IParam& param,
                                                  SSDInterface* ssd) {
  return new CommandExit();
}

static CommandFactoryRegisterer register_Exit{eExitCmd,
                                               new FactoryExitCommand()};
