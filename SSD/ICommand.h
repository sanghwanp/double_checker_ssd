#pragma once

#include "IParam.h"
#include "FileDriver.h"

class ICommand {
 public:
  virtual ~ICommand() {}
  virtual void Execute(IParam* param) {
    FileDriver FD = FileDriver::GetInstance();

    FD.SaveFile(READ_OUTPUT_FILE_NAME, "ERROR");
  }

};