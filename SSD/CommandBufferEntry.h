#pragma once
#include <stdexcept>
#include <string>

#include "CommandBufferConfig.h"

class CommandBufferEntry {
 public:
  CommandBufferConfig::CmdType cmdType;
  unsigned int startLba, endLba;
  unsigned long long data;

  CommandBufferEntry();
  CommandBufferEntry(CommandBufferConfig::CmdType cmdType,
                     unsigned int startLba, unsigned int endLba,
                     unsigned long long data);

  CommandBufferEntry(unsigned int startLba, unsigned int endLba,
                     unsigned long long data);

  int Length() const;

  std::string ToString() const;
  void Print() const;

 private:
  void Validator();
  CommandBufferConfig::CmdType GetCmdType() const;
  unsigned int GetStartLba() const;
  unsigned int GetEndLba() const;
  unsigned long long GetData() const;
};
