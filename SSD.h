#pragma once
#include <vector>
class SSD {
 public:
  const int STORAGE_SIZE = 100;
  const int STORAGE_INIT_VALUE = 0;
  SSD() { clear(); }
  void clear() {
    storage.clear();
    storage.resize(STORAGE_SIZE, STORAGE_INIT_VALUE);
  }
  unsigned int read(int lba) { return storage[lba]; }

private:
  std::vector<unsigned int> storage;
};
