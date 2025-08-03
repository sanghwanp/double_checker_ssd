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
  CommandBufferEntry(CMD_TYPE cmdType, unsigned int startLba = 0,
                     unsigned int endLba = 0, unsigned long long data = 0);

  int Length() const;

  std::string ToString() const;
  std::string ToString(CMD_TYPE cmdType) const;
  void Print() const;

  CommandBufferEntry(unsigned int startLba, unsigned int endLba,
                     unsigned long long data);
public:
    bool operator==(const CommandBufferEntry& other) const {
        return cmdType == other.cmdType &&
            startLba == other.startLba &&
            endLba == other.endLba &&
            data == other.data;
    }
    bool operator!=(const CommandBufferEntry& other) const {
        return !(*this == other);
    }
 private:
  void Validator();
};
