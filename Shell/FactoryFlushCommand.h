#pragma once
#include "ICommandFactory.h"

class FactoryFlushCommand : public ICommandFactory {
 public:
  FactoryFlushCommand() = default;
  IShellCommand* CreateCommand(IParam& param, SSDInterface* ssd) override;
};
