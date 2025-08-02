#include "CmdFullWrite.h"
#include "CommandFactoryRegisterer.h"
#include "FactoryFullWriteCommand.h"
#include "IParam.h"

IShellCommand* FactoryFullWriteCommand::CreateCommand(IParam& param,
                                                 SSDInterface* ssd) {
  return new CommandFullWrite(ssd);
}

static CommandFactoryRegisterer register_FullWrite{ eFullwriteCmd, new FactoryFullWriteCommand()};
