#pragma once

#include "ITestScriptCase.h"

class TestScriptCase4 : public ITestScriptCase {
 public:
  TestScriptCase4(SSDInterface* ssdinterface);
  virtual bool Call() override;
};
