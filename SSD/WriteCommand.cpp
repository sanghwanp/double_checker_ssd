#include "WriteCommand.h"

#include <cstring>
#include <fstream>
#include <iomanip>

bool WriteCommand::Execute(IParam* param) {
    auto* writeparam = dynamic_cast<WriteParam*>(param);
  if (!writeparam) return false;

    FileDriver FD = FileDriver::GetInstance();
    FD.SetBufferData(writeparam->lba.val, writeparam->data.val);
    FD.SaveFile(STORAGE_FILE_NAME, FD.GetBufferData(0), MAX_STORAGE_IDX);
    return true;
}
