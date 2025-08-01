#include "CmdErase.h"
#include "FactoryEraseCommand.h"
#include "CommandFactoryRegisterer.h"
#include "IParam.h"

IShellCommand* FactoryEraseCommand::CreateCommand(IParam& param, SSDInterface* ssd) {
    return new CommandErase(ssd);
}

static CommandFactoryRegisterer register_erase{ eEraseCmd, new FactoryEraseCommand() };

