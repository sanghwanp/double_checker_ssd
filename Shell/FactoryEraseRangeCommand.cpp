#include "CmdEraseRange.h"
#include "CommandFactoryRegisterer.h"
#include "FactoryEraseRangeCommand.h"
#include "IParam.h"

IShellCommand* FactoryEraseRangeCommand::CreateCommand(IParam& param,
                                                      SSDInterface* ssd) {
  return new CommandEraseRange(ssd);
}

static CommandFactoryRegisterer register_EraseRange{
    eEraseRangeCmd, new FactoryEraseRangeCommand()};
