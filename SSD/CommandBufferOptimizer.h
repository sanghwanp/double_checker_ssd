#pragma once
#include <vector>

#include "CommandBufferEntry.h"

namespace {
constexpr int INF = 0x3f3f3f3f;
constexpr int NA = -1;
}  // namespace

class CommandBufferOptimizer {
 public:
  std::vector<CommandBufferEntry> Optimize(
      const std::vector<CommandBufferEntry> &in_cmds);
  // std::vector<CommandBufferEntry> Optimize(const
  // std::vector<CommandBufferEntry> &in_cmds);

 private:
  const unsigned long long INIT_ORDER_MASK = (1ULL << 32);
  const unsigned long long REAL_DATA_MASK = INIT_ORDER_MASK - 1;
  const int MAX_ERASE_RANGE_SIZE = 10;
};
