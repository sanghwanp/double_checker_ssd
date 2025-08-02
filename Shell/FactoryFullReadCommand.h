#pragma once
#include "ICommandFactory.h"

class FactoryFullReadCommand : public ICommandFactory {
 public:
  FactoryFullReadCommand() = default;
  IShellCommand* CreateCommand(IParam& param, SSDInterface* ssd) override;
};
