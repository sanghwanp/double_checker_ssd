#pragma once

#include <string>
#include <vector>
#include <memory>

#include "SSDInterface.h"
#include "IParam.h"
#include "ITestScriptCase.h"

class CommandTestScript {
 public:
  CommandTestScript(SSDInterface* ssdInterface);
  bool Call(const IParam& param);

 private:
  SSDInterface* ssd;
  std::vector<std::unique_ptr<ITestScriptCase>> cases;
};
