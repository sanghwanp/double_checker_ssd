#pragma once
#include <vector>
class SSD {
 public:
  SSD() { clear(); }
  void clear() {
    storage.clear();
    storage.resize(100, 0);
  }
  int read(int lba) { return storage[lba]; }

  std::vector<int> storage;
};
