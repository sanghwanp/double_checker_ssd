#pragma once
#include <string>
#include <vector>

class CommandExit {
 public:
  bool Call(const std::vector<std::string>& tokens);
};