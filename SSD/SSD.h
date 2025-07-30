#pragma once
#include <vector>

#include "ReadArguments.h"
#include "ReadCmd.h"

class SSD {
 public:
  SSD();

 public:
  void Clear();
  unsigned int Read(ReadArguments& readArgs);

 private:
  const int STORAGE_SIZE = 100;
  const int STORAGE_INIT_VALUE = 0;
  std::vector<unsigned int> storage;
  ReadCmd readCmd;
};
