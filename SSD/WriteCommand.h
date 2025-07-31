#pragma once
#include "ICommand.h"


class WriteCommand : public ICommand {
 public:
  void Execute(IParam* param) override {
    auto* writeparam = dynamic_cast<WriteParam*>(param);
    if (!writeparam) return;
    
    FileDriver FD = FileDriver::GetInstance();
    FD.SetBufferData(writeparam->lba.val, writeparam->data.val);
    FD.SaveFile(STORAGE_FILE_NAME, FD.GetBufferData(0), MAX_STORAGE_IDX);
  }
};
