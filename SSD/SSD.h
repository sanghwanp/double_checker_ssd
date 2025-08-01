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

  static SSD& GetInstance() {
    static SSD instance;
    return instance;
  }

  void Run(vector<string> argv);
  void ExecuteCommand(IParam* param);

  unsigned int GetCachedData(unsigned int lba);

 private:
  CommandFactory* commandFactory;
  FileDriver* filedriver;
  Parser parser;
};
