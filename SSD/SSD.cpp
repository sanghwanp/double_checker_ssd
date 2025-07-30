#include "SSD.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

SSD::SSD() { Clear(); }
void SSD::Clear() {
  storage.clear();
  storage.resize(STORAGE_SIZE, STORAGE_INIT_VALUE);
}

void SSD::SetWriteCmd(ICmd *cmd) { this->writeCmd = cmd; }

void SSD::SetReadCmd(ICmd *cmd) { this->readCmd = cmd; }

void SSD::SaveToOutputFile(unsigned int readData) {
  std::ofstream ofs;
  ofs.open("C:\\ssd_output.txt");
  ofs << (std::stringstream() << std::hex << readData).str();
  ofs.close();
}

// unsigned int SSD::Read(int lba) const { return readCmd.Run(lba, storage); }
unsigned int SSD::Read(IArguments *args) {
  unsigned int readData = readCmd->Run(args);
  // unsigned int readData = dynamic_cast<ReadCmd *>(readCmd)->GetReadResult();
  SaveToOutputFile(readData);
  return readData;
}

void SSD::Write(IArguments *args) { writeCmd->Run(args); }
