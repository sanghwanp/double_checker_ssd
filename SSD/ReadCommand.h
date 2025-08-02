#pragma once
#include "ICommand.h"

class ReadCommand : public ICommand {
 public:
  bool Execute(IParam* param, bool isBufferEnablede) override;
  bool CheckPrecondition() override;
  void ReadData(const std::string& outval);
  std::string ReadCommand::ToString(unsigned int val);

 private:
  ReadParam* readParam;
  bool ExecuteWithCommandBuffer(IParam *param);
  bool ExecuteWithoutCommandBuffer(IParam *param);
};
