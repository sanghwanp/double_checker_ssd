#include "FlushCommand.h"
#include "CommandBufferEntry.h"

bool FlushCommand::Execute(IParam* param) {

  std::vector<CommandBufferEntry> entry = cmdBufHandler.Flush();

  for (auto item : entry) {
    if (item.cmdType == eWriteCmd) {
      for (unsigned int lba = item.startLba; lba <= item.endLba; lba++) {
        fileDriver->SetBufferData(lba, item.data);
      }
    }
    else if (item.cmdType == eEraseCmd) {
      for (unsigned int lba = item.startLba; lba <= item.endLba; lba++) {
        fileDriver->SetBufferData(lba, 0);
      }
    }
  }

  SaveFile();
  return true;
}

void FlushCommand::SaveFile() {
  fileDriver->SaveFile(STORAGE_FILE_NAME, fileDriver->GetBufferAddr(), MAX_STORAGE_IDX);
}
