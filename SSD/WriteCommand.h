#pragma once

#include <vector>
#include <string>
#include "ICommand.h"

using namespace std;

class WriteCommand : public ICommand {
 public:
  bool Execute(IParam* param, bool isBufferEnabled) override;
  bool CheckPrecondition() override;

  void UpdateDataBuffer();
  void SaveCommandBuffer();
  void SaveFile();

 private:
  WriteParam* writeParam;
  vector<string> cmds;
  bool ExecuteWithCommandBuffer(IParam *param);
  bool ExecuteWithoutCommandBuffer(IParam *param);
};
