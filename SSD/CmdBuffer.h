#pragma once
#include <vector>

#include "Interval.h"

namespace {
constexpr int INF = 0x3f3f3f3f;
constexpr int NA = -1;
}  // namespace

using LBA = unsigned int;
using DATA = unsigned long long;
class CmdBuffer {
 public:
  std::vector<Interval> Optimize(const std::vector<Interval> &in_cmds);

 private:
  const unsigned int STORAGE_SIZE = 100;
  const unsigned long long INIT_ORDER_MASK = (1ULL << 32);
  const unsigned long long REAL_DATA_MASK = INIT_ORDER_MASK - 1;
  const int MAX_ERASE_RANGE_SIZE = 10;
};
