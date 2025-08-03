#include "CommandFactory.h"
#include "EraseCommand.h"
#include "FlushCommand.h"
#include "ReadCommand.h"
#include "WriteCommand.h"

#include <iostream>
using namespace std;
CommandFactory::CommandFactory(FileDriver* fileDriver,
                               CommandBufferHandler* bufferHandler)
    : fileDriver(fileDriver), bufferHandler(bufferHandler) {}

std::unique_ptr<ICommand> CommandFactory::GetCommand(CMD_TYPE cmdType) {
  std::unique_ptr<ICommand> command;
  cout << "CommandFactory::GetCommand : " << cmdType << endl;
  cout << &fileDriver << " " << &bufferHandler << endl;
  switch (cmdType) {
    case eWriteCmd:
      std::cout << "Creating WriteCommand" << std::endl;
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
      std::cerr << "Unknown command type: " << cmdType << std::endl;
      break;
  }
  cout << command << endl;
  return command;
}

std::unique_ptr<ICommand> CommandFactory::CreateReadCommand() {
  return std::make_unique<ReadCommand>(fileDriver, bufferHandler, this);
}

std::unique_ptr<ICommand> CommandFactory::CreateWriteCommand() {
  cout << "CommandFactory::CreateWriteCommand " << &fileDriver << "  "
       << bufferHandler << " " << this << endl;
  return std::make_unique<WriteCommand>(fileDriver, bufferHandler, this);
}

std::unique_ptr<ICommand> CommandFactory::CreateEraseCommand() {
  return std::make_unique<EraseCommand>(fileDriver, bufferHandler, this);
}

std::unique_ptr<ICommand> CommandFactory::CreateFlushCommand() {
  return std::make_unique<FlushCommand>(fileDriver, bufferHandler);
}
