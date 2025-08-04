#include "CommandFactory.h"
#include "EraseCommand.h"
#include "FlushCommand.h"
#include "ReadCommand.h"
#include "WriteCommand.h"

CommandFactory::CommandFactory(FileDriver* fileDriver,
                               CommandBufferHandler* bufferHandler)
    : fileDriver(fileDriver), bufferHandler(bufferHandler) {}

std::unique_ptr<ICommand> CommandFactory::GetCommand(CMD_TYPE cmdType) {
  std::unique_ptr<ICommand> command;
  switch (cmdType) {
    case eWriteCmd:
      command = CreateWriteCommand();
      break;
    case eReadCmd:
      command = CreateReadCommand();
      break;
    case eEraseCmd:
      command = CreateEraseCommand();
      break;
    case eFlushCmd:
      command = CreateFlushCommand();
      break;
    default:
      command = nullptr;
      break;
  }
  return command;
}

std::unique_ptr<ICommand> CommandFactory::CreateReadCommand() {
  return std::make_unique<ReadCommand>(fileDriver, bufferHandler, this);
}

std::unique_ptr<ICommand> CommandFactory::CreateWriteCommand() {
  return std::make_unique<WriteCommand>(fileDriver, bufferHandler, this);
}

std::unique_ptr<ICommand> CommandFactory::CreateEraseCommand() {
  return std::make_unique<EraseCommand>(fileDriver, bufferHandler, this);
}

std::unique_ptr<ICommand> CommandFactory::CreateFlushCommand() {
  return std::make_unique<FlushCommand>(fileDriver, bufferHandler);
}
