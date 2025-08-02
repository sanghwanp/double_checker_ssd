#include "EraseCommand.h"

#include "CommandBufferHandler.h"
#include "FileDriver.h"
#include "WriteCommand.h"

bool EraseCommand::Execute(IParam* param, bool isBufferEnabled) {
    if(isBufferEnabled) {
        return ExecuteWithCommandBuffer(param);
    }
    else {
        return ExecuteWithoutCommandBuffer(param);
    }
}

bool EraseCommand::ExecuteWithCommandBuffer(IParam* param) {
  eraseParam = dynamic_cast<EraseParam*>(param);
  if (!CheckPrecondition()) return false;

  SaveCommandBuffer();
  return true;
}

bool EraseCommand::ExecuteWithoutCommandBuffer(IParam* param) {
  eraseParam = dynamic_cast<EraseParam*>(param);
  if (!CheckPrecondition()) return false;
  UpdateDataBuffer();
  SaveFile();
  return true;
}

bool EraseCommand::CheckPrecondition() {
  if (!eraseParam) return false;
  if (eraseParam->lba.val >= MAX_STORAGE_IDX) return false;
  if (eraseParam->size.val > MAX_ERASE_SIZE) return false;
  if (eraseParam->lba.val + eraseParam->size.val > MAX_STORAGE_IDX)
    return false;
  return true;
}

void EraseCommand::UpdateDataBuffer() {
  for (size_t size = 0; size < eraseParam->size.val; size++) {
    int lba = eraseParam->lba.val + size;
    fileDriver->SetBufferData(lba, 0);
  }
}

void EraseCommand::SaveFile() {
  fileDriver->SaveFile(STORAGE_FILE_NAME, fileDriver->GetBufferAddr(), MAX_STORAGE_IDX);
}

void EraseCommand::SaveCommandBuffer() {
  vector<CommandBufferEntry> cmds =
      cmdBufHandler.AddErase(eraseParam->lba.val, eraseParam->size.val);

  for(const CommandBufferEntry &cmd: cmds) {
      IParam *param = cmd.TransformToIParam();
      if(cmd.cmdType == CMD_TYPE::eEraseCmd) {
          Execute(param, false);
      }
      else if(cmd.cmdType == CMD_TYPE::eWriteCmd) {
          WriteCommand wCommand;
          wCommand.Execute(param, false);
      }
      else {
          throw std::exception("Invalid COmmand was returned at CommandBuffer");
      }
  }
}
