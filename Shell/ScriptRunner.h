#pragma once
#include <istream>
#include <string>

#include "SSDInterface.h"

class ScriptRunner {
 public:
  ScriptRunner(SSDInterface* ssd, const std::string& scriptPath);
  void Run();

 private:
  SSDInterface* ssd;
  std::string scriptPath;

  static constexpr const char* TEST1_LONG = "1_FullWriteAndReadCompare";
  static constexpr const char* TEST1_SHORT = "1_";
  static constexpr const char* TEST2_LONG = "2_PartialLBAWrite";
  static constexpr const char* TEST2_SHORT = "2_";
  static constexpr const char* TEST3_LONG = "3_WriteReadAging";
  static constexpr const char* TEST3_SHORT = "3_";
  static constexpr const char* TEST4_LONG = "4_EraseAndWriteAging";
  static constexpr const char* TEST4_SHORT = "4_";
};
