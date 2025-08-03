#pragma once

#include "CommandBufferHandler.h"
#include "CommandFactory.h"
#include "FileDriver.h"
#include "ICommand.h"
#include "IParam.h"

class EraseCommand : public ICommand {
 public:
  explicit EraseCommand(FileDriver* fileDriver,
                        CommandBufferHandler* bufferHandler,
                        CommandFactory* factory);

  bool Execute(IParam* param) override;
  bool CheckPrecondition() override;

 private:
  void Erase();
  void SaveDataBuffer();
  void SaveCommandBuffer();

  FileDriver* fileDriver;
  CommandBufferHandler* bufferHandler;
  CommandFactory* factory;

  EraseParam* eraseParam;
};
