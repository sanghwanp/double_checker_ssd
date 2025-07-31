#pragma once
#define interface struct
#include <string>

interface IArguments {
 public:
  virtual ~IArguments() = default;
  virtual unsigned int GetLba() const = 0;
  virtual void Parse(const std::string& cmdStr) = 0;
};
