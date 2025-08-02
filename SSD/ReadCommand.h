#pragma once

#include "CommandBufferHandler.h"
#include "CommandFactory.h"
#include "FileDriver.h"
#include "ICommand.h"
#include "IParam.h"

class ReadCommand : public ICommand {
 public:
  explicit ReadCommand(FileDriver* fileDriver,
                       CommandBufferHandler* bufferHandler,
                       CommandFactory* factory);

  bool Execute(IParam* param) override;
  bool CheckPrecondition() override;

 private:
  void Read();
  void ReadCommandBuffer(unsigned int& data);
  void ReadDataBuffer(unsigned int& data);

  FileDriver* fileDriver;
  CommandBufferHandler* bufferHandler;
  CommandFactory* factory;

  ReadParam* readParam;
};
