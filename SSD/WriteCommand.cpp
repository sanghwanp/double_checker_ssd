#include "WriteCommand.h"

WriteCommand::WriteCommand(FileDriver* fileDriver,
                           CommandBufferHandler* bufferHandler,
                           CommandFactory* factory)
    : fileDriver(fileDriver),
      bufferHandler(bufferHandler),
      factory(factory),
      writeParam(nullptr) {}

bool WriteCommand::Execute(IParam* param) {
  writeParam = dynamic_cast<WriteParam*>(param);

  if (!CheckPrecondition()) return false;

  Write();
  return true;
}

void WriteCommand::Write() {
#if (USING_COMMAND_BUFFER == 1)
  SaveCommandBuffer();
#else
  SaveDataBuffer();
#endif
}

bool WriteCommand::CheckPrecondition() {
  if (!fileDriver || !bufferHandler || !factory) return false;
  if (!writeParam) return false;
  if (writeParam->lba.val >= MAX_STORAGE_IDX) return false;
  return true;
}

void WriteCommand::SaveCommandBuffer() {
  std::vector<CommandBufferEntry> entry =
      bufferHandler->AddWrite(writeParam->lba.val, writeParam->data.val);

  if (entry.empty()) return;

  for (auto item : entry) {
    for (unsigned int lba = item.startLba; lba <= item.endLba; lba++) {
      fileDriver->SetBufferData(lba, item.data);
    }
  }
  fileDriver->StoreData();
}

void WriteCommand::SaveDataBuffer() {
  fileDriver->SetBufferData(writeParam->lba.val, writeParam->data.val);
  fileDriver->StoreData();
}
