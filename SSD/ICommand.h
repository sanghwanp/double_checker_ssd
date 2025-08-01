#pragma once

#include "IParam.h"
#include "FileDriver.h"

class ICommand {
 public:
  virtual ~ICommand() {}

  virtual bool Execute(IParam* param) { return false; }

};
