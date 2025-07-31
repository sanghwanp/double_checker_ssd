#pragma once
#include <string>

class ILogger {
 public:
  virtual void print(const std::string& functionName,
                     const std::string& message) = 0;
};
