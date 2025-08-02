#pragma once
#include "IParam.h"
#include "SSDInterface.h"

class IShellCommand {
 public:
  virtual bool Call(IParam& param) = 0;
};

class IScriptCommand {
 public:
  virtual std::string Call(IParam& param) = 0;
};
