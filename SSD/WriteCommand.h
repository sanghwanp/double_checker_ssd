#pragma once

#include <vector>
#include <string>
#include "ICommand.h"

using namespace std;

class WriteCommand : public ICommand {
 public:
  bool Execute(IParam* param) override;
  bool CheckPrecondition() override;

  void UpdateDataBuffer();
  void SaveCommandBuffer();
  void SaveFile();

 private:
  WriteParam* writeParam;
  vector<string> cmds;
};
