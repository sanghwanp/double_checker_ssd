#pragma once
#include "ReadArguments.h"
#include "WriteArguments.h"

#define interface struct
interface ICmd {
  virtual ~ICmd() = default;
  virtual void Run(IArguments * args) = 0;
};
