#include "CommandFactory.h"

#include "ReadCommand.h"
#include "WriteCommand.h"

CommandFactory::CommandFactory() { RegisterAllCommands(); }

void CommandFactory::RegisterAllCommands() {
  Register(eWriteCmd, []() { return new WriteCommand(); });
  Register(eReadCmd, []() { return new ReadCommand(); });
}