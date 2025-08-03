#include "FlushCommand.h"

FlushCommand::FlushCommand(FileDriver* fileDriver,
                           CommandBufferHandler* bufferHandler)
    : fileDriver(fileDriver), bufferHandler(bufferHandler) {}

bool FlushCommand::Execute(IParam* param) {
  if (!CheckPrecondition()) return false;
  Flush();
  return true;
}

bool FlushCommand::CheckPrecondition() {
  if (!fileDriver || !bufferHandler) return false;
  return true;
}

void FlushCommand::Flush() {

#if (USING_COMMAND_BUFFER == 1)
  std::vector<CommandBufferEntry> entry = bufferHandler->Flush();
  for (auto item : entry) {
    for (unsigned int lba = item.startLba; lba <= item.endLba; lba++) {
      fileDriver->SetBufferData(lba, item.data);
    }
  }
#endif

  fileDriver->StoreData();
}
