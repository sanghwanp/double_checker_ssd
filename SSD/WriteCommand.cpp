#include "WriteCommand.h"

#include "FileDriver.h"
#include "EraseCommand.h"

bool WriteCommand::Execute(IParam* param, bool isBufferEnabled) {
  if (isBufferEnabled) {
    return ExecuteWithCommandBuffer(param);
  } else {
    return ExecuteWithoutCommandBuffer(param);
  }
}

bool WriteCommand::ExecuteWithCommandBuffer(IParam* param) {
  writeParam = dynamic_cast<WriteParam*>(param);
  if (!CheckPrecondition()) return false;

  SaveCommandBuffer();
  return true;
}

bool WriteCommand::ExecuteWithoutCommandBuffer(IParam* param) {
  writeParam = dynamic_cast<WriteParam*>(param);
  if (!CheckPrecondition()) return false;

  UpdateDataBuffer();
  SaveFile();
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
  fileDriver->SaveFile(STORAGE_FILE_NAME, fileDriver->GetBufferAddr(),
                       MAX_STORAGE_IDX);
}

void WriteCommand::SaveCommandBuffer() {
  vector<CommandBufferEntry> cmds =
      cmdBufHandler.AddWrite(writeParam->lba.val, writeParam->data.val);
  if (cmds.empty()) return;
  for (const CommandBufferEntry& cmd : cmds) {
    IParam* param = cmd.TransformToIParam();
    if (cmd.cmdType == CMD_TYPE::eWriteCmd) {
      Execute(param, false);
    } else if (cmd.cmdType == CMD_TYPE::eEraseCmd) {
      EraseCommand eCommand;
      eCommand.Execute(param, false);
    } else {
      throw std::exception("Invalid Command was returned at CommandBuffer");
    }
  }
}
