#pragma once
#include "ICommand.h"


class WriteCommand : public ICommand {
 public:
     void Execute(IParam* param) override;
};
