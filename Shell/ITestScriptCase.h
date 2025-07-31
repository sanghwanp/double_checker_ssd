#pragma once

#include <string>
#include <random>

#include "SSDInterface.h"

class ITestScriptCase {
 public:
  ITestScriptCase(SSDInterface* ssdinterface, int number);
  virtual ~ITestScriptCase() = default;

  bool ReadCompare(std::string lba, std::string expected);
  std::string GetRandomInputData();
  void PrintPassResult();
  void PrintFailResult();
  virtual bool Call() = 0;

  SSDInterface* ssd;
  int number;

  const std::string TEST_SCRIPT_PASS_OUTPUT = "PASS";
  const std::string TEST_SCRIPT_FAIL_OUTPUT = "FAIL";
};
