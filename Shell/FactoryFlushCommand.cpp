#include "CmdFlush.h"
#include "CommandFactoryRegisterer.h"
#include "FactoryFlushCommand.h"
#include "IParam.h"

IShellCommand* FactoryFlushCommand::CreateCommand(IParam& param,
                                                  SSDInterface* ssd) {
  return new CommandFlush(ssd);
}

static CommandFactoryRegisterer register_Flush{eFlushCmd,
                                               new FactoryFlushCommand()};
