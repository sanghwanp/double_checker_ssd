#pragma once
#include "ICommandFactory.h"

class FactoryReadCommand : public ICommandFactory {
 public:
  FactoryReadCommand() = default;
  IShellCommand* CreateCommand(IParam& param, SSDInterface* ssd) override;
};
