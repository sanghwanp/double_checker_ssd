#pragma once
#include <iostream>

#include "ICommand.h"

class WriteCommand : public ICommand {
 public:
  void Execute(IParam* param) override {
    auto* writeparam = dynamic_cast<WriteParam*>(param);
    if (!writeparam) return;
    
  }
};
