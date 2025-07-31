#pragma once
#include <vector>

#include "SSDConfig.h"
#include "FileDriver.h"
#include "Parser.h"

#include "IParam.h"
#include "ICmd.h"

#include "ReadArguments.h"
#include "ReadCmd.h"

#include "WriteArguments.h"
#include "WriteCmd.h"

using std::string;

class SSD {
 public:
  SSD();

  static SSD instance;
  static SSD &GetInstance() { return instance; }

  void Format();
  void Open();

  bool Run(vector<string> argv);
  void SetWriteCmd(ICmd *cmd);
  void SetReadCmd(ICmd *cmd);
  unsigned int Read(IArguments *args);
  void Write(IArguments *args);
  unsigned int GetCachedData(unsigned int lba);

 private:
  void SaveToOutputFile(unsigned int readData);

  FileDriver filedriver;
  Parser parser;

  vector<unsigned int> cache;
  unsigned int storageCache[MAX_STORAGE_IDX] = {0};

  ICmd *writeCmd = nullptr;
  ICmd *readCmd = nullptr;
};
