#include "WriteCommand.h"

#include "FileDriver.h"
#include "FlushCommand.h"

WriteCommand::WriteCommand(CommandBufferHandler* buf, FileDriver* file, CommandFactory* factory)
    : bufferHandler(buf), fileDriver(file), factory(factory) {}

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

#if 0
#include "WriteCommand.h"

WriteCommand::WriteCommand(FileDriver* fileDriver,
                           CommandBufferHandler* bufferHandler,
                           CommandFactory* factory)
    : fileDriver(fileDriver), bufferHandler(bufferHandler), factory(factory) {}

bool WriteCommand::CheckPrecondition() {
    // 예시: 버퍼 존재 여부
    return bufferHandler != nullptr && fileDriver != nullptr;
}

bool WriteCommand::Execute(IParam* param) {
    // 실제 쓰기 로직 + 조건에 따라 factory 사용
    if (param == nullptr) return false;

    // 예시 로직
    bufferHandler->BufferWrite(param);

    if (/* flush 필요 */) {
        auto flushCmd = factory->CreateFlushCommand();
        return flushCmd->Execute(nullptr);
    }

    return true;
}

#endif
