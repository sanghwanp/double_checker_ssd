#include "CommandFactory.h"

#include "ReadCommand.h"
#include "WriteCommand.h"
#include "EraseCommand.h"
#include "FlushCommand.h"

CommandFactory::CommandFactory() { RegisterAllCommands(); }

void CommandFactory::RegisterAllCommands() {
  Register(eWriteCmd, [this]() { return std::make_unique<WriteCommand>(this);
  Register(eReadCmd,  [this]() { return std::make_unique<ReadCommand>(this);
  Register(eEraseCmd, [this]() { return std::make_unique<EraseCommand>(this);
  Register(eFlushCmd, [this]() { return std::make_unique<FlushCommand>(this);
}


#if 0
#include "CommandFactory.h"
#include "EraseCommand.h"
#include "FlushCommand.h"
#include "ReadCommand.h"
#include "WriteCommand.h"

CommandFactory::CommandFactory(FileDriver* fileDriver, CommandBufferHandler* bufferHandler)
    : fileDriver(fileDriver), bufferHandler(bufferHandler) {}

std::unique_ptr<ICommand> CommandFactory::CreateWriteCommand() {
    return std::make_unique<WriteCommand>(fileDriver, bufferHandler, this);
}

std::unique_ptr<ICommand> CommandFactory::CreateFlushCommand() {
    return std::make_unique<FlushCommand>(fileDriver);
}

std::unique_ptr<ICommand> CommandFactory::CreateEraseCommand() {
    return std::make_unique<EraseCommand>(fileDriver);
}

std::unique_ptr<ICommand> CommandFactory::CreateReadCommand() {
    return std::make_unique<ReadCommand>(fileDriver);
}

#endif
