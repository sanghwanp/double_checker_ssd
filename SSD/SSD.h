#pragma once
#include <vector>

#include "SSDConfig.h"
#include "CommandFactory.h"
#include "FileDriver.h"
#include "Parser.h"

#include "ICommand.h"
#include "WriteCommand.h"
#include "ReadCommand.h"
#include "ReadArguments.h"
#include "WriteArguments.h"

using std::string;

class SSD {
 public:
  SSD();

  static SSD instance;
  static SSD &GetInstance() { return instance; }

  void Format();
  void Open();

  unsigned int Read(IArguments *args);
  void Write(IArguments *args);
  void Run(vector<string> argv);
  unsigned int GetCachedData(unsigned int lba);

 private:
  void SaveToOutputFile(unsigned int readData);
  
  CommandFactory commandFactory;

  FileDriver filedriver;
  Parser parser;

  vector<unsigned int> cache;
  unsigned int storageCache[MAX_STORAGE_IDX] = {0};

  ICommand *writeCmd = nullptr;
  ICommand *readCmd = nullptr;
};
