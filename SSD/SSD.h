#pragma once
#include <vector>
#include "IArguments.h"
#include "ICmd.h"
#include "ReadArguments.h"
#include "ReadCmd.h"
#include "WriteArguments.h"
#include "WriteCmd.h"
#include "SsdConfig.h"

class SSD {
 public:
  SSD();

 public:
  void Clear();
  void SetWriteCmd(ICmd *cmd);
  void SetReadCmd(ICmd *cmd);
  unsigned int Read(IArguments *args);
  void Write(IArguments *args);
  unsigned int GetCachedData(unsigned int lba);

 private:
  void SaveToOutputFile(unsigned int readData);
  std::vector<unsigned int> cache;
  // ReadCmd readCmd;
  ICmd *writeCmd = nullptr;
  ICmd *readCmd = nullptr;
};
