#pragma once

#include <string>
#include <vector>
#include <memory>

#include "SSDInterface.h"
#include "IParam.h"
#include "ITestScriptCase.h"
#include "ICommand.h"

class CommandTestScript {
 public:
  CommandTestScript(SSDInterface* ssdInterface);
  std::string CallSciprt(const IParam& param);

 private:
  SSDInterface* ssd;
  std::vector<std::unique_ptr<ITestScriptCase>> cases;
};
