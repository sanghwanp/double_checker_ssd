#pragma once
#include <vector>
#include "IArguments.h"
#include "ICmd.h"
#include "ReadArguments.h"
#include "ReadCmd.h"
#include "WriteArguments.h"
#include "WriteCmd.h"

class SSD {
 public:
  SSD();

 public:
  void Clear();
  void SetWriteCmd(ICmd *cmd);
  void SetReadCmd(ICmd *cmd);
  unsigned int Read(IArguments *args);
  void Write(IArguments *args);

 private:
  void SaveToOutputFile(unsigned int readData);
  const int STORAGE_SIZE = 100;
  const int STORAGE_INIT_VALUE = 0;
  std::vector<unsigned int> storage;
  // ReadCmd readCmd;
  ICmd *writeCmd = nullptr;
  ICmd *readCmd = nullptr;
};
