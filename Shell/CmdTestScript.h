#pragma once

#include <string>
#include <vector>
#include <memory>

#include "SSDInterface.h"
#include "IParam.h"
#include "ITestScriptCase.h"
#include "ICommand.h"

class CommandTestScript : public IScriptCommand {
 public:
  CommandTestScript(SSDInterface* ssdInterface);
  std::string Call(IParam& param) override;

 private:
  SSDInterface* ssd;
  std::vector<std::unique_ptr<ITestScriptCase>> cases;
};
