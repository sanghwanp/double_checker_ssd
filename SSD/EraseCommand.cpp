#include "EraseCommand.h"

#include "FlushCommand.h"

EraseCommand::EraseCommand(FileDriver* fileDriver,
                           CommandBufferHandler* bufferHandler,
                           CommandFactory* factory)
    : fileDriver(fileDriver),
      bufferHandler(bufferHandler),
      factory(factory),
      eraseParam(nullptr) {}

bool EraseCommand::Execute(IParam* param) {
  eraseParam = dynamic_cast<EraseParam*>(param);

  if (!CheckPrecondition()) return false;

  Erase();
  return true;
}

void EraseCommand::Erase() {
#if (USING_COMMAND_BUFFER == 1)
  SaveCommandBuffer();
#else
  SaveDataBuffer();
#endif
}

bool EraseCommand::CheckPrecondition() {
  if (!fileDriver || !bufferHandler || !factory) return false;
  if (!eraseParam) return false;
  if (eraseParam->lba.val >= MAX_STORAGE_IDX) return false;
  if (eraseParam->size.val > MAX_ERASE_SIZE) return false;
  if (eraseParam->lba.val + eraseParam->size.val > MAX_STORAGE_IDX)
    return false;
  return true;
}
void EraseCommand::SaveCommandBuffer() {
  std::vector<CommandBufferEntry> entry =
      bufferHandler->AddErase(eraseParam->lba.val, eraseParam->size.val);

  if (entry.empty()) return;

  for (auto item : entry) {
    for (unsigned int lba = item.startLba; lba <= item.endLba; lba++) {
      fileDriver->SetBufferData(lba, item.data);
    }
  }
  fileDriver->StoreData();
}

void EraseCommand::SaveDataBuffer() {
  for (size_t size = 0; size < eraseParam->size.val; size++) {
    int lba = eraseParam->lba.val + size;
    fileDriver->SetBufferData(lba, 0);
  }
  fileDriver->StoreData();
}
