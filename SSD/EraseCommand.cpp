#include "EraseCommand.h"

#include "CommandBufferHandler.h"
#include "FileDriver.h"
#include "WriteCommand.h"

bool EraseCommand::Execute(IParam* param) {
  eraseParam = dynamic_cast<EraseParam*>(param);

  if (!CheckPrecondition()) return false;

#if (USING_COMMAND_BUFFER == 1)
  SaveCommandBuffer();
#else
  UpdateDataBuffer();
  SaveFile();
#endif
  return true;
}

bool EraseCommand::CheckPrecondition() {
  if (!eraseParam) return false;
  if (eraseParam->lba.val >= MAX_STORAGE_IDX) return false;
  if (eraseParam->size.val > MAX_ERASE_SIZE) return false;
  if (eraseParam->lba.val + eraseParam->size.val > MAX_STORAGE_IDX)
    return false;
  return true;
}

void EraseCommand::UpdateDataBuffer() {
  for (size_t size = 0; size < eraseParam->size.val; size++) {
    int lba = eraseParam->lba.val + size;
    fileDriver->SetBufferData(lba, 0);
  }
}

void EraseCommand::SaveFile() {
  fileDriver->SaveFile(STORAGE_FILE_NAME, fileDriver->GetBufferAddr(), MAX_STORAGE_IDX);
}

void EraseCommand::SaveCommandBuffer() {
  cmdBufHandler.AddErase(eraseParam->lba.val, eraseParam->size.val);
}
