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
