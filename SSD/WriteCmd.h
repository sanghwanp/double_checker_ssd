#pragma once

#include "ICommand.h"

class WriteCmd {
 public:
  bool CheckFirst();
  void Init();
  void Run(CommandArguments cmd);
  void SetData(int i, uint d);

  uint nand[MAX_LBA_SIZE];
  CommandArguments cmd;
};
