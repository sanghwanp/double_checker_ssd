#pragma once

#include "SSDConfig.h"
#include "IParam.h"
#include "FileDriver.h"

#include "CommandBufferHandler.h"

class ICommand {
 public:
  ICommand() { fileDriver = FileDriver::GetInstance(); }
  virtual ~ICommand() {}

  virtual bool Execute(IParam* param) { return false; }
  virtual bool CheckPrecondition() { return false; }

#if (USING_COMMAND_BUFFER == 1)
  CommandBufferHandler cmdBufHandler;
#endif
  FileDriver* fileDriver = FileDriver::GetInstance();
};
