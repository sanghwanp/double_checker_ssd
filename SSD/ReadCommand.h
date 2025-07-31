#pragma once
#include "ICommand.h"
#include "FileDriver.h"

class ReadCommand : public ICommand {
 public:
  void Execute(IParam *param) override {
    auto *readParam = dynamic_cast<ReadParam *>(param);
    if (!readParam) return;
    FileDriver FD = FileDriver::GetInstance();
    
    FD.SaveFile(READ_OUTPUT_FILE_NAME, FD.GetBufferData(readParam->lba.val), 1);
  }

};