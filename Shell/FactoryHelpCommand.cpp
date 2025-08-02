#include "CmdHelp.h"
#include "CommandFactoryRegisterer.h"
#include "FactoryHelpCommand.h"
#include "IParam.h"

IShellCommand* FactoryHelpCommand::CreateCommand(IParam& param,
                                                  SSDInterface* ssd) {
  return new CommandHelp();
}

static CommandFactoryRegisterer register_Help{eHelpCmd,
                                               new FactoryHelpCommand()};
