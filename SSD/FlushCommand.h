#pragma once
#include "ICommand.h"

class FlushCommand : public ICommand {
 public:
  bool Execute(IParam* param, bool isEnabledBuffer=false) override;

  void SaveFile();
};
