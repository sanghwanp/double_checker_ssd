#pragma once
#include "ICommand.h"
#include "FileDriver.h"

class ReadCommand : public ICommand {
 public:
     void Execute(IParam* param) override;
};
