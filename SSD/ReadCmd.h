#pragma once
#include <vector>
class ReadCmd {
 public:
  unsigned int Run(int lba, const std::vector<unsigned int> &storage);
};
