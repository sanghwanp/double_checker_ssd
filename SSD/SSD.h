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
  SSD(FileDriver* fileDriver, CommandBufferHandler* bufferHandler,
      CommandFactory* commandFactory);

  static SSD& GetInstance(FileDriver* fileDriver,
                          CommandBufferHandler* bufferHandler,
                          CommandFactory* commandFactory) {
    static SSD instance(fileDriver, bufferHandler, commandFactory);
    return instance;
  }

  void Run(IParam* cmd);
  bool ExecuteCommand(IParam* param);

  unsigned int GetCachedData(unsigned int lba);

 private:
  FileDriver* fileDriver;
  CommandBufferHandler* bufferHandler;
  CommandFactory* commandFactory;
  Parser parser;
};
