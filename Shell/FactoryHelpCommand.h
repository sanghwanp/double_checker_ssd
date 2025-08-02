#pragma once
#include "ICommandFactory.h"

class FactoryHelpCommand : public ICommandFactory {
 public:
  FactoryHelpCommand() = default;
  IShellCommand* CreateCommand(IParam& param, SSDInterface* ssd) override;
};
