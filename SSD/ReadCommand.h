#pragma once
#include "ICommand.h"

class ReadCommand : public ICommand {
 public:
     bool Execute(IParam* param) override;
};
