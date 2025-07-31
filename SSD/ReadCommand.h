#pragma once
#include "ICommand.h"

class ReadCommand : public ICommand {
 public:
  void Execute(IParam *param) override {
    auto *readParam = dynamic_cast<ReadParam *>(param);
    if (!readParam) return;

  }
};