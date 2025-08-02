#pragma once
#include <string>

class ILogger {
 public:
  virtual void LogPrint(const std::string& functionName,
                     const std::string& message, bool bConsole = true) = 0;
  virtual void SetConsoleOutput(bool on) = 0;
  static ILogger* GetInstance();
};
