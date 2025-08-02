#include "ReadCommand.h"

#include <iostream>
ReadCommand::ReadCommand(FileDriver* fileDriver,
                         CommandBufferHandler* bufferHandler,
                         CommandFactory* factory)
    : fileDriver(fileDriver),
      bufferHandler(bufferHandler),
      factory(factory),
      readParam(nullptr) {}

bool ReadCommand::Execute(IParam* param) {
  readParam = dynamic_cast<ReadParam*>(param);

  if (!CheckPrecondition()) return false;

  Read();

  return true;
}

bool ReadCommand::CheckPrecondition() {
  if (!fileDriver || !bufferHandler || !factory) return false;
  if (!readParam) return false;
  if (readParam->lba.val >= MAX_STORAGE_IDX) return false;
  return true;
}

void ReadCommand::Read() {
  unsigned int data = 0;

#if (USING_COMMAND_BUFFER == 1)
  ReadCommandBuffer(data);
#else
  ReadDataBuffer(data);
#endif

  fileDriver->StoreOutput(data);
}

void ReadCommand::ReadCommandBuffer(unsigned int& data) {
  if (!bufferHandler->TryFastRead(readParam->lba.val, data)) data = 0;
  fileDriver->SetBufferData(readParam->lba.val, data);
}

void ReadCommand::ReadDataBuffer(unsigned int& data) {
  data = fileDriver->GetBufferData(readParam->lba.val);
}
