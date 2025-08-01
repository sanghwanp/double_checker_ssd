#include "FlushCommand.h"

#include "CommandBufferEntry.h"

bool FlushCommand::Execute(IParam* param) {
  std::vector<CommandBufferEntry> entry = cmdBufHandler.Flush();

  for (auto item : entry) {
    for (unsigned int lba = item.startLba; lba <= item.endLba; lba++) {
      fileDriver->SetBufferData(lba, item.data);
    }
  }

  SaveFile();
  return true;
}

void FlushCommand::Flush(std::vector<CommandBufferEntry> entry) {
  for (auto item : entry) {
    for (unsigned int lba = item.startLba; lba <= item.endLba; lba++) {
      fileDriver->SetBufferData(lba, item.data);
    }
  }

  SaveFile();
}

void FlushCommand::SaveFile() {
  fileDriver->SaveFile(STORAGE_FILE_NAME, fileDriver->GetBufferAddr(), MAX_STORAGE_IDX);
}
