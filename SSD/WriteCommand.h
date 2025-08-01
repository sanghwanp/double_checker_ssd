#pragma once
#include "ICommand.h"

class WriteCommand : public ICommand {
 public:
     bool Execute(IParam* param) override;
};
