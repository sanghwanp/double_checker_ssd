#include "SSD.h"

SSD::SSD() { Clear(); }
void SSD::Clear() {
  storage.clear();
  storage.resize(STORAGE_SIZE, STORAGE_INIT_VALUE);
}

//unsigned int SSD::Read(int lba) const { return readCmd.Run(lba, storage); }
unsigned int SSD::Read(ReadArguments &readArgs) {
  readCmd.Run(&readArgs);
  return readCmd.GetOutputData();
}
