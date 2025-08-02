#pragma once

#include <memory>

#include "CommandBufferHandler.h"
#include "FileDriver.h"
#include "ICommand.h"

class CommandFactory {
 public:
  CommandFactory() {}
  CommandFactory(FileDriver* fileDriver, CommandBufferHandler* bufferHandler);

  static CommandFactory* GetInstance() {
    static CommandFactory instance(FileDriver::GetInstance(),
                                   CommandBufferHandler::GetInstance());
    return &instance;
  }
  std::unique_ptr<ICommand> GetCommand(CMD_TYPE cmdType);
  std::unique_ptr<ICommand> CreateReadCommand();
  std::unique_ptr<ICommand> CreateWriteCommand();
  std::unique_ptr<ICommand> CreateEraseCommand();
  std::unique_ptr<ICommand> CreateFlushCommand();

 private:
  FileDriver* fileDriver;
  CommandBufferHandler* bufferHandler;
};
