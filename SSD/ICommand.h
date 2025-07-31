#pragma once
#include <vector>

#include "IParam.h"


class ICommand {
 public:
  virtual ~ICommand() {}
  virtual void Execute(IParam* param) = 0;

};