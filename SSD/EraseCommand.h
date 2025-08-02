#pragma once
#include "ICommand.h"

class EraseCommand : public ICommand {
 public:
  bool Execute(IParam* param) override;
  bool CheckPrecondition() override;

  void UpdateDataBuffer();
  void SaveCommandBuffer();
  void SaveFile();

 private:
  EraseParam* eraseParam;
};
