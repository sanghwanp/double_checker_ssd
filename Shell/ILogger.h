#pragma once
#include <string>

class ILogger {
  virtual void print(const std::string& location, const std::string& message) = 0;
};
