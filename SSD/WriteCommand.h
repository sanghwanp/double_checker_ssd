#pragma once

#include "CommandBufferHandler.h"
#include "CommandFactory.h"
#include "FileDriver.h"
#include "ICommand.h"
#include "IParam.h"

class WriteCommand : public ICommand {
 public:
  explicit WriteCommand(FileDriver* fileDriver,
                        CommandBufferHandler* bufferHandler,
                        CommandFactory* factory);

  bool Execute(IParam* param) override;
  bool CheckPrecondition() override;

 private:
  void Write();
  void SaveDataBuffer();
  void SaveCommandBuffer();

  FileDriver* fileDriver;
  CommandBufferHandler* bufferHandler;
  CommandFactory* factory;

  WriteParam* writeParam;
};
