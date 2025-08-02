#include "CommandFactory.h"

#include "ReadCommand.h"
#include "WriteCommand.h"
#include "EraseCommand.h"
#include "FlushCommand.h"

CommandFactory::CommandFactory() { RegisterAllCommands(); }

void CommandFactory::RegisterAllCommands() {
  Register(eWriteCmd, []() { return new WriteCommand(); });
  Register(eReadCmd, []() { return new ReadCommand(); });
  Register(eEraseCmd, []() { return new EraseCommand(); });
  Register(eFlushCmd, []() { return new FlushCommand(); });
}
