#pragma once
#include <stdexcept>
#include <string>

#include "CommandBufferConfig.h"

class CommandBufferEntry {
 public:
  CommandBufferConfig::CmdType cmdType;  // 0: Write, 1: Erase
  int startLba, endLba;
  unsigned long long data;

  CommandBufferEntry();
  CommandBufferEntry(CommandBufferConfig::CmdType cmdType, unsigned int startLba,
                     unsigned int endLba, unsigned long long data);

  int Length() const;

  std::string ToString() const;
  std::string ToString(CommandBufferConfig::CmdType cmdType) const;
  void Print() const;

  CommandBufferEntry(unsigned int startLba, unsigned int endLba,
                     unsigned long long data);

 private:
  void Validator();
};
