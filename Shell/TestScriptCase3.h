#pragma once

#include "ITestScriptCase.h"

class TestScriptCase3 : public ITestScriptCase {
 public:
  TestScriptCase3(SSDInterface* ssdinterface);
  virtual bool Call() override;
};
