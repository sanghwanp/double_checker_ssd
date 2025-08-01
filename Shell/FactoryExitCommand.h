#pragma once
#include "ICommandFactory.h"

class FactoryExitCommand : public ICommandFactory {
 public:
  FactoryExitCommand() = default;
  IShellCommand* CreateCommand(IParam& param, SSDInterface* ssd) override;
};
