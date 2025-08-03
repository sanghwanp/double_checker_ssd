#pragma once
#include <stdexcept>
#include <string>

#include "CommandBufferConfig.h"

class CommandBufferEntry {
 public:
  CMD_TYPE cmdType;  // 0: Write, 1: Erase
  int startLba, endLba;
  unsigned long long data;

  CommandBufferEntry();
  CommandBufferEntry(CMD_TYPE cmdType, unsigned int startLba,
                     unsigned int endLba, unsigned long long data);

  int Length() const;

  std::string ToString() const;

  CommandBufferEntry(unsigned int startLba, unsigned int endLba,
                     unsigned long long data);

 private:
  void Validator();
};
