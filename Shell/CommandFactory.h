#pragma once
#include "IParam.h"
#include "SSDInterface.h"
#include "ICommandFactory.h"
#include <map>

class CommandFactory : public ICommandFactory {
 public:
  static CommandFactory* GetInstance() {
    static CommandFactory instance;
    return &instance;
  }
  IShellCommand* CreateCommand(IParam& Param, SSDInterface* ssd) override;
  void Register(TestShellCMD cmd, ICommandFactory* factory);

 private:
  CommandFactory() = default;
  ~CommandFactory() = default;

  CommandFactory(const CommandFactory&) = delete;
  CommandFactory& operator=(const CommandFactory&) = delete;

  std::map<TestShellCMD, ICommandFactory*> factories;

};
