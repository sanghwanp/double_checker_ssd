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
  if (bufferHandler->IsBufferFull()) {
    auto flushCmd = factory->CreateFlushCommand();
    flushCmd->Execute((IParam*)writeParam);
  }

  bufferHandler->AddWrite(writeParam->lba.val, writeParam->data.val);
}

void WriteCommand::SaveDataBuffer() {
  fileDriver->SetBufferData(writeParam->lba.val, writeParam->data.val);
  fileDriver->StoreData();
}
