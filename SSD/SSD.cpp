#include "SSD.h"

SSD::SSD() { Clear(); }
void SSD::Clear() {
  storage.clear();
  storage.resize(STORAGE_SIZE, STORAGE_INIT_VALUE);
}

void SSD::SetWriteCmd(ICmd *cmd) { this->writeCmd = cmd; }

void SSD::SetReadCmd(ICmd *cmd) { this->readCmd = cmd; }

// unsigned int SSD::Read(int lba) const { return readCmd.Run(lba, storage); }
unsigned int SSD::Read(ReadArguments &readArgs) {
  readCmd->Run(&readArgs);
  return dynamic_cast<ReadCmd *>(readCmd)->GetOutputData();
}

void SSD::Write(IArguments &args) { writeCmd->Run(&args); }
