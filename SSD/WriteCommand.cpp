#include "WriteCommand.h"

#include "FileDriver.h"
#include "FlushCommand.h"

bool WriteCommand::Execute(IParam* param) {
  writeParam = dynamic_cast<WriteParam*>(param);

  if (!CheckPrecondition()) return false;

#if (USING_COMMAND_BUFFER == 1)
  SaveCommandBuffer();
#else
  UpdateDataBuffer();
  SaveFile();
#endif
  return true;
}

bool WriteCommand::CheckPrecondition() {
  if (!writeParam) return false;
  if (writeParam->lba.val >= MAX_STORAGE_IDX) return false;
  return true;
}

void WriteCommand::UpdateDataBuffer() {
  fileDriver->SetBufferData(writeParam->lba.val, writeParam->data.val);
}

void WriteCommand::SaveFile() {
  fileDriver->SaveFile(STORAGE_FILE_NAME, fileDriver->GetBufferAddr(), MAX_STORAGE_IDX);
}

void WriteCommand::SaveCommandBuffer() {
  std::vector<CommandBufferEntry> entry = cmdBufHandler.AddWrite(writeParam->lba.val, writeParam->data.val);
  if (entry.size()) {
    std::unique_ptr<FlushCommand> FC= std::make_unique<FlushCommand>();
    FC->Flush(entry);
  }
}
