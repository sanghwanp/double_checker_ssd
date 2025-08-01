#pragma once
#include <string>
#include <vector>
#include "ICommand.h"

class CommandExit : public IShellCommand {
 public:
  bool Call(IParam& param) override;
};
