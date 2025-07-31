#pragma once

#include "ITestScriptCase.h"

class TestScriptCase1 : public ITestScriptCase {
 public:
  TestScriptCase1(SSDInterface* ssdinterface);
  virtual bool Call() override;
};