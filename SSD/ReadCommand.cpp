#include "ReadCommand.h"

bool ReadCommand::Execute(IParam* param) {
    auto* readParam = dynamic_cast<ReadParam*>(param);
  if (!readParam) return false;
    if (readParam->lba.val >= MAX_STORAGE_IDX) return false;
    FileDriver FD = FileDriver::GetInstance();

    FD.SaveFile(OUTPUT_FILE_NAME, FD.GetBufferData(readParam->lba.val), 1);
    return true;
}
