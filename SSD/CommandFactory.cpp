#include "CommandFactory.h"

#include "ReadCommand.h"
#include "WriteCommand.h"
#include "EraseCommand.h"

CommandFactory::CommandFactory() { RegisterAllCommands(); }

void CommandFactory::RegisterAllCommands() {
  Register(eWriteCmd, []() { return new WriteCommand(); });
  Register(eReadCmd, []() { return new ReadCommand(); });
  Register(eEraseCmd, []() { return new EraseCommand(); });
}
