#pragma once
#include <vector>

#include "ReadCmd.h"

class SSD {
 public:
  SSD();

 public:
  void Clear();
  unsigned int Read(int lba) const;

 private:
  const int STORAGE_SIZE = 100;
  const int STORAGE_INIT_VALUE = 0;
  std::vector<unsigned int> storage;
  ReadCmd readCmd;
};
