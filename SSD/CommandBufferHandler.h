#pragma once
#include <vector>

#include "CommandBuffer.h"
#include "CommandBufferEntry.h"
#include "CommandBufferOptimizer.h"

class CommandBufferHandler {
 public:
  static CommandBufferHandler *GetInstance() {
    static CommandBufferHandler instance;  // 유일한 인스턴스를 static으로 생성
    return &instance;
  }

  bool CheckBufferFull();
  std::vector<CommandBufferEntry> AddWrite(unsigned int lba, unsigned int data);
  std::vector<CommandBufferEntry> AddErase(unsigned int lba, int delta);
  bool TryFastRead(unsigned int lba, unsigned int &out_value) const;
  void InitCommandBufferEntry();
  std::vector<CommandBufferEntry> Flush();

 private:
  CommandBuffer commandBuffer;
  CommandBufferOptimizer commandBufferOptimizer;

  bool IsFullCmds(std::vector<CommandBufferEntry> &cmds);
  int GetStartLba(int lba, int delta) const;
  int GetEndLba(int lba, int delta) const;
};
