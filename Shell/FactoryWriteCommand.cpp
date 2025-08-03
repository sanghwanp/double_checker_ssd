#include "CmdWrite.h"
#include "FactoryWriteCommand.h"
#include "CommandFactoryRegisterer.h"
#include "IParam.h"
#include "SnowEffect.h"

IShellCommand* FactoryWriteCommand::CreateCommand(IParam& param, SSDInterface* ssd) {
    return new CommandWrite(ssd);
}

static CommandFactoryRegisterer register_Write{ eWriteCmd, new FactoryWriteCommand() };


IShellCommand* FactorySnowflake::CreateCommand(IParam& param, SSDInterface* ssd) {
    return new SnowEffect();
}

static CommandFactoryRegisterer register_DoubleChecker{ eDoubleChecker, new FactorySnowflake() };

