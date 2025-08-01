#pragma once
#include "ICommand.h"
#include "IParam.h"
#include "SSDInterface.h"

class CommandFactory : public ICommandFactory {
 public:
  static CommandFactory* GetInstance() {
    static CommandFactory instance;
    return &instance;
  }
  IShellCommand* CreateCommand(IParam& Param, SSDInterface* ssd) override;

 private:
  CommandFactory();
  ~CommandFactory() = default;

  CommandFactory(const CommandFactory&) = delete;
  CommandFactory& operator=(const CommandFactory&) = delete;

  SSDInterface* ssdInterface;
};
