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
  void ExecuteCommand(IParam* param);

  unsigned int GetCachedData(unsigned int lba);

 private:
  CommandFactory* commandFactory;
  FileDriver* filedriver;
  Parser parser;
};


#if 0
class SSD {
public:
    SSD()
        : fileDriver(),
          bufferHandler(),
          factory(&fileDriver, &bufferHandler)
    {}

    bool ExecuteCommand(CommandType type, IParam* param);

private:
    FileDriver fileDriver;
    CommandBufferHandler bufferHandler;
    CommandFactory factory;
};

#endif
