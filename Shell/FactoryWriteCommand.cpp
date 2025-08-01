#include "CmdWrite.h"
#include "FactoryWriteCommand.h"
#include "CommandFactoryRegisterer.h"
#include "IParam.h"

IShellCommand* FactoryWriteCommand::CreateCommand(IParam& param, SSDInterface* ssd) {
    return new CommandWrite(ssd);
}

static CommandFactoryRegisterer register_Write{ eWriteCmd, new FactoryWriteCommand() };
