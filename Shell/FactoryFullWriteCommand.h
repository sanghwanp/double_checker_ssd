#pragma once
#include "ICommandFactory.h"

class FactoryFullWriteCommand : public ICommandFactory {
 public:
  FactoryFullWriteCommand() = default;
  IShellCommand* CreateCommand(IParam& param, SSDInterface* ssd) override;
};
