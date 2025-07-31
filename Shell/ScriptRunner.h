#pragma once
#include <iostream>
#include <vector>
#include <string>

class ScriptRunner {
 public:
  ScriptRunner(std::istream& in);
  void run();

 private:
  std::istream& in;

  const std::string TEST_SCRIPT_1_SHORT = "1_";
  const std::string TEST_SCRIPT_2_SHORT = "2_";
  const std::string TEST_SCRIPT_3_SHORT = "3_";
  const std::string TEST_SCRIPT_4_SHORT = "4_";
  const std::string TEST_SCRIPT_1_LONG = "1_FullWriteAndReadCompare";
  const std::string TEST_SCRIPT_2_LONG = "2_PartialLBAWrite";
  const std::string TEST_SCRIPT_3_LONG = "3_WriteReadAging";
  const std::string TEST_SCRIPT_4_LONG = "4_EraseAndWriteAging";
  const std::string PRINT_RUN_COMMAND = " ___ Run... ";
  const std::string PRINT_PASS_COMMAND = "Pass";
  const std::string PRINT_FAIL_COMMAND = "Fail!";
  const std::string PRINT_INVALID_COMMAND = ": INVALID SCRIPT";
};