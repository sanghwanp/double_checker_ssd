#pragma once
#include "ICommandFactory.h"

class FactoryEraseRangeCommand : public ICommandFactory {
 public:
  FactoryEraseRangeCommand() = default;
  IShellCommand* CreateCommand(IParam& param, SSDInterface* ssd) override;
};
