#pragma once
#include <vector>

#include "ReadArguments.h"
#include "ReadCmd.h"

class SSD {
 public:
  SSD();

 public:
  void Clear();
  void SetWriteCmd(ICmd *cmd);
  void SetReadCmd(ICmd *cmd);
  unsigned int Read(ReadArguments &readArgs);
  void Write(IArguments &args);

 private:
  const int STORAGE_SIZE = 100;
  const int STORAGE_INIT_VALUE = 0;
  std::vector<unsigned int> storage;
  // ReadCmd readCmd;
  ICmd *writeCmd = nullptr;
  ICmd *readCmd = nullptr;
};
