#pragma once
#include "ICommand.h"
#include "IParam.h"
#include "SSDInterface.h"

class ICommandFactory {
 public:
  virtual IShellCommand* CreateCommand(IParam& Param, SSDInterface* ssd) = 0;
  static ICommandFactory* GetInstance();
};
