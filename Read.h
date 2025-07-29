#pragma once
#include <vector>
class Read {
 public:
  unsigned int run(int lba, const std::vector<unsigned int>& storage) {
    return storage[lba];
  }
};
