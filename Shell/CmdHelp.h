#pragma once
#include<vector>
#include<string>

class CommandHelp {
 public:
  bool Call(const std::vector<std::string>& program);
};