#pragma once
#include <vector>

#include "ReadCmd.h"

class SSD {
 public:
  const int STORAGE_SIZE = 100;
  const int STORAGE_INIT_VALUE = 0;
  SSD() { Clear(); }
  void Clear() {
    storage.clear();
    storage.resize(STORAGE_SIZE, STORAGE_INIT_VALUE);
  }

  unsigned int Read(int lba) { return readCmd.Run(lba, storage); }

 private:
  std::vector<unsigned int> storage;
  ReadCmd readCmd;
};
