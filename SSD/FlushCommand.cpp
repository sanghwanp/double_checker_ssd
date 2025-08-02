#include "FlushCommand.h"

#include "CommandBufferEntry.h"

bool FlushCommand::Execute(IParam* param) {
  Flush(cmdBufHandler.Flush());
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


#if 0
#include "FlushCommand.h"

FlushCommand::FlushCommand(FileDriver* fileDriver)
    : fileDriver(fileDriver) {}

bool FlushCommand::CheckPrecondition() {
    return fileDriver != nullptr;
}

bool FlushCommand::Execute(IParam* param) {
    // 예시: 캐시나 버퍼를 플러시
    return fileDriver->Flush();
}

#endif
