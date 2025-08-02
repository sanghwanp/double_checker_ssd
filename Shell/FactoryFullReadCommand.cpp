#include "CmdFullRead.h"
#include "CommandFactoryRegisterer.h"
#include "FactoryFullReadCommand.h"
#include "IParam.h"

IShellCommand* FactoryFullReadCommand::CreateCommand(IParam& param,
                                                  SSDInterface* ssd) {
  return new CommandFullRead(ssd);
}

static CommandFactoryRegisterer register_FullRead{eFullreadCmd,
                                              new FactoryFullReadCommand()};
