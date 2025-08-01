#pragma once

#include "ITestScriptCase.h"

class TestScriptCase2 : public ITestScriptCase {
 public:
  TestScriptCase2(SSDInterface* ssdinterface);
  virtual bool Call() override;
};
