#pragma once
#include "IParam.h"
class IShellCommand {
 public:
  virtual bool Call(IParam& param) = 0;
};

class ICommandFactory {
 public:
  virtual IShellCommand* CreateCommand(IParam& Param) = 0;
  virtual ~ICommandFactory() = default;
  static ICommandFactory* GetInstance();
};
