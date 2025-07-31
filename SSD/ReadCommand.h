#pragma once
#include <vector>
#include <string>

#include "ICommand.h"
#include "ReadArguments.h"
#include "SSDConfig.h"

class ReadCommand : public ICommand {
 public:
  void Execute(IParam *param) override {
    auto *readParam = dynamic_cast<ReadParam *>(param);
    if (!readParam) return;

  }
};