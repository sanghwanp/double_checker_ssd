#pragma once
#include <vector>

#include "CommandBuffer.h"
#include "CommandBufferEntry.h"
#include "CommandBufferOptimizer.h"

class CommandBufferHandler {
 public:
  void AddWrite(unsigned int lba, unsigned long long data);
  void AddErase(unsigned int lba);
  std::vector<CommandBufferEntry> Flush();

 private:
  CommandBuffer buffer;
  CommandBufferOptimizer optimizer;
};
