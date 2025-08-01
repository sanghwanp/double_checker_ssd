#pragma once
#include <vector>

#include "CommandBuffer.h"
#include "CommandBufferEntry.h"
#include "CommandBufferOptimizer.h"

class CommandBufferHandler {
 public:
  std::vector<CommandBufferEntry> AddWrite(unsigned int lba, unsigned int data);
  std::vector<CommandBufferEntry> AddErase(unsigned int lba, int delta);
  bool TryFastRead(unsigned int lba, unsigned int &out_value) const;

  std::vector<CommandBufferEntry> Flush();

 private:
  CommandBuffer commandBuffer;
  CommandBufferOptimizer commandBufferOptimizer;

  bool IsFullCmds(std::vector<CommandBufferEntry> &cmds);
  int GetStartLba(int lba, int delta) const;
  int GetEndLba(int lba, int delta) const;
};
