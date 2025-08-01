#pragma once
#include "ICommand.h"

class EraseCommand : public ICommand {
 public:
  bool Execute(IParam* param) override;
};
