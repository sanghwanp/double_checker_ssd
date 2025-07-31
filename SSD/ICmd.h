#pragma once
#include <vector>

#include "ReadArguments.h"
#include "WriteArguments.h"

#define interface struct
interface ICmd {
  virtual ~ICmd() = default;
  virtual unsigned int Run(IArguments * args,
                           std::vector<unsigned int> & cache) = 0;
};
