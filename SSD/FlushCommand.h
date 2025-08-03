#pragma once

#include "CommandBufferHandler.h"
#include "FileDriver.h"
#include "ICommand.h"

class FlushCommand : public ICommand {
 public:
  explicit FlushCommand(FileDriver* fileDriver,
                        CommandBufferHandler* bufferHandler);

  bool Execute(IParam* param) override;
  bool CheckPrecondition() override;

 private:
  void Flush();

  FileDriver* fileDriver;
  CommandBufferHandler* bufferHandler;
};
