#include "WriteCommand.h"

#include "FileDriver.h"

bool WriteCommand::Execute(IParam* param) {
  auto* writeparam = dynamic_cast<WriteParam*>(param);
  if (!writeparam) return false;
  if (writeparam->lba.val >= MAX_STORAGE_IDX) return false;

  FileDriver* FD = FileDriver::GetInstance();
  FD->SetBufferData(writeparam->lba.val, writeparam->data.val);
  FD->SaveFile(STORAGE_FILE_NAME, FD->GetBufferAddr(), MAX_STORAGE_IDX);
  return true;
}
