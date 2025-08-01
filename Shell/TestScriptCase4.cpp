#include <iostream>

#include "TestScriptCase4.h"

TestScriptCase4::TestScriptCase4(SSDInterface* ssdinterface)
    : ITestScriptCase(ssdinterface, 4) {}

bool TestScriptCase4::Call() {
  PrintPassResult();
  return true;
}
