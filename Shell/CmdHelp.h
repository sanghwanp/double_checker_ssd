#pragma once
#include<vector>
#include<string>
#include "ICommand.h"

class CommandHelp : public IShellCommand {
 public:
  bool Call(IParam& param) override;
};
