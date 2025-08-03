#include "CmdWrite.h"
#include "FactoryWriteCommand.h"
#include "CommandFactoryRegisterer.h"
#include "IParam.h"
#include "CmdDouble.h"

IShellCommand* FactoryWriteCommand::CreateCommand(IParam& param, SSDInterface* ssd) {
    return new CommandWrite(ssd);
}

static CommandFactoryRegisterer register_Write{ eWriteCmd, new FactoryWriteCommand() };


IShellCommand* FactoryDoubleCommand::CreateCommand(IParam& param, SSDInterface* ssd) {
    return new CommandDouble();
}

static CommandFactoryRegisterer register_DoubleChecker{ eDoubleCmd, new FactoryDoubleCommand() };

