#pragma once
#include "ICommand.h"

class ReadCommand : public ICommand {
 public:
  bool Execute(IParam* param) override;
  bool CheckPrecondition() override;
  void ReadData(const std::string& outval);
  std::string ReadCommand::ToString(unsigned int val);

 private:
  ReadParam* readParam;
};
