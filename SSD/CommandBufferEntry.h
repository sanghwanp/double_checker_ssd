#pragma once
#include <stdexcept>
#include <string>

#include "CommandBufferConfig.h"

enum class CmdType { READ, WRITE, ERASE, INVALID };
class CommandBufferEntry {
 public:
  CmdType cmdType;  // 0: Write, 1: Erase
  int startLba, endLba;
  unsigned long long data;

  CommandBufferEntry();
  CommandBufferEntry(CmdType cmdType, unsigned int startLba,
                     unsigned int endLba, unsigned long long data);

  int Length() const;

  std::string ToString(CmdType cmdType) const;
  void Print() const;

  CommandBufferEntry(unsigned int startLba, unsigned int endLba,
                     unsigned long long data);

 private:
  void Validator();
};
