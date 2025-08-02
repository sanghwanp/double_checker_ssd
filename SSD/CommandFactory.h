#pragma once
#include <functional>
#include <memory>
#include <unordered_map>

#include "ICommand.h"

class CommandFactory {
 public:
  CommandFactory();

  static CommandFactory* GetInstance() {
    static CommandFactory instance;
    return &instance;
  }

  void Register(CMD_TYPE cmd, std::function<ICommand*()> creator) {};
  void RegisterAllCommands();

  ICommand* Create(CMD_TYPE cmd) const {
    auto it = registry.find(cmd);
    if (it != registry.end()) {
      return it->second();
    }
    return nullptr;
  }

 private:
  std::unordered_map<CMD_TYPE, std::function<ICommand*()>> registry;
};


#if 0
#pragma once

#include <memory>

#include "CommandBufferHandler.h"
#include "FileDriver.h"
#include "ICommand.h"

class CommandFactory {
public:
    CommandFactory(FileDriver* fileDriver, CommandBufferHandler* bufferHandler);

    std::unique_ptr<ICommand> CreateWriteCommand();
    std::unique_ptr<ICommand> CreateFlushCommand();
    std::unique_ptr<ICommand> CreateEraseCommand();
    std::unique_ptr<ICommand> CreateReadCommand();

private:
    FileDriver* fileDriver;
    CommandBufferHandler* bufferHandler;
};

#endif
