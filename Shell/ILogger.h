#pragma once
#include <string>

class ILogger {
 public:
  virtual void LogPrint(const std::string& functionName,
                     const std::string& message) = 0;
  virtual void MyPrint(const std::string& message) = 0;
};
