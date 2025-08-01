#include "ReadCommand.h"

#include "FileDriver.h"

bool ReadCommand::Execute(IParam* param) {
  readParam = dynamic_cast<ReadParam*>(param);

  if (!CheckPrecondition()) return false;

  unsigned int outval;
#if (USING_COMMAND_BUFFER == 1)
  if (cmdBufHandler.TryFastRead(readParam->lba.val, outval))
    fileDriver->SetBufferData(readParam->lba.val, outval);
#endif
  outval = fileDriver->GetBufferData(readParam->lba.val);

  ReadData(ToString(outval));

  return true;
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
  ss << std::hex << val;  // 16진수로 변환
  return "0x" + ss.str();
}
