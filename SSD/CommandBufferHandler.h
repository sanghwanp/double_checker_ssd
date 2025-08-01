#pragma once
#include <vector>

#include "CommandBuffer.h"
#include "CommandBufferEntry.h"
#include "CommandBufferOptimizer.h"

class CommandBufferHandler {
 public:
  void AddWrite(unsigned int lba, unsigned int data);
  void AddErase(unsigned int lba, int delta);
  bool TryFastRead(unsigned int lba, unsigned int & out_value);
  std::vector<CommandBufferEntry> Flush();

 private:
  CommandBuffer buffer;
  CommandBufferOptimizer optimizer;

  int GetStartLba(int lba, int delta) const;
  int GetEndLba(int lba, int delta) const;
};
