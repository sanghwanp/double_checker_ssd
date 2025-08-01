#pragma once
#include <vector>

#include "SSDConfig.h"
#include "CommandFactory.h"
#include "FileDriver.h"
#include "Parser.h"

#include "ICommand.h"

using std::string;

class SSD {
 public:
     SSD();

  static SSD instance;
  static SSD &GetInstance() { return instance; }

  void Run(vector<string> argv);
  void ExecuteCommand(IParam *param);

  unsigned int GetCachedData(unsigned int lba);

 private:
  CommandFactory commandFactory;
  FileDriver filedriver;
  Parser parser;

  vector<unsigned int> cache;
  unsigned int storageCache[MAX_STORAGE_IDX] = {0};

};
