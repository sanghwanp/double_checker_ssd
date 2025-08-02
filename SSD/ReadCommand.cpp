#include "ReadCommand.h"

#include "FileDriver.h"

bool ReadCommand::Execute(IParam* param, bool isBufferEnabled) {
  if (isBufferEnabled) {
    return ExecuteWithCommandBuffer(param);
  } else {
    return ExecuteWithoutCommandBuffer(param);
  }
}

bool ReadCommand::CheckPrecondition() {
  if (!readParam) return false;
  if (readParam->lba.val >= MAX_STORAGE_IDX) return false;
  return true;
}

void ReadCommand::ReadData(const std::string& outval) {
  fileDriver->SaveFile(OUTPUT_FILE_NAME, outval);
}

std::string ReadCommand::ToString(unsigned int val) {
  std::stringstream ss;
  ss << std::hex << std::setw(8) << std::setfill('0') << val;  // 16진수로 변환
  return "0x" + ss.str();
}

bool ReadCommand::ExecuteWithCommandBuffer(IParam* param) {
  readParam = dynamic_cast<ReadParam*>(param);
  if (!CheckPrecondition()) return false;

  unsigned int outval;
  if (cmdBufHandler.TryFastRead(readParam->lba.val, outval)) {
    fileDriver->SetBufferData(readParam->lba.val, outval);
  }
  outval = fileDriver->GetBufferData(readParam->lba.val);
  ReadData(ToString(outval));
  return true;
}
bool ReadCommand::ExecuteWithoutCommandBuffer(IParam* param) {
  readParam = dynamic_cast<ReadParam*>(param);
  if (!CheckPrecondition()) return false;

  unsigned int outval = fileDriver->GetBufferData(readParam->lba.val);
  ReadData(ToString(outval));
  return true;
}
