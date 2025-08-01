#include "EraseCommand.h"
#include "WriteCommand.h"
#include "FileDriver.h"

bool EraseCommand::Execute(IParam* param) {
  auto* eraseParam = dynamic_cast<EraseParam*>(param);
  if (!eraseParam) return false;
  if (eraseParam->lba.val >= MAX_STORAGE_IDX) return false;
  if (eraseParam->size.val > MAX_ERASE_SIZE) return false;
  if (eraseParam->lba.val + eraseParam->size.val > MAX_STORAGE_IDX)
    return false;

  FileDriver* FD = FileDriver::GetInstance();
  for (size_t size = 0; size < eraseParam->size.val; size++) {
    int lba = eraseParam->lba.val + size;
    FD->SetBufferData(lba, 0);
  }
  FD->SaveFile(STORAGE_FILE_NAME, FD->GetBufferAddr(), MAX_STORAGE_IDX);
}
