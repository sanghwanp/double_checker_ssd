#pragma once
#include <vector>

#include "CommandFactory.h"
#include "FileDriver.h"
#include "ICommand.h"
#include "Parser.h"
#include "SSDConfig.h"

using std::string;

class SSD {
 public:
  SSD();

  static SSD& GetInstance() {
    static SSD instance;
    return instance;
  }

  void Run(vector<string> argv);
  bool ExecuteCommand(IParam* param);

  unsigned int GetCachedData(unsigned int lba);

 private:
  FileDriver* fileDriver;
  CommandBufferHandler* bufferHandler;
  CommandFactory* commandFactory;
  Parser parser;
};
