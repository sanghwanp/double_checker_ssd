#include "CmdRead.h"
#include "CommandFactoryRegisterer.h"
#include "FactoryReadCommand.h"
#include "IParam.h"

IShellCommand* FactoryReadCommand::CreateCommand(IParam& param,
                                                  SSDInterface* ssd) {
  return new CommandRead(ssd);
}

static CommandFactoryRegisterer register_Read{eReadCmd, new FactoryReadCommand()};
