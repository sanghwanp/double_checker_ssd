#pragma once

#include <string>
#include <random>

#include "SSDInterface.h"

class ITestScriptCase {
 public:
  ITestScriptCase(SSDInterface* ssdinterface, int number, std::string name);
  virtual ~ITestScriptCase() = default;

  std::string GetName();
  std::string GetFullName();
  int GetNumber();

  bool ReadCompare(std::string lba, std::string expected);
  std::string GetRandomInputData();
  static void PrintPassResult();
  static void PrintFailResult();
  virtual bool Call() = 0;

  SSDInterface* ssd;
  const int number;
  const std::string name;

  static const std::string TEST_SCRIPT_PASS_OUTPUT;
  static const std::string TEST_SCRIPT_FAIL_OUTPUT;
};
