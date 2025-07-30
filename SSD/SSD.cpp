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

// unsigned int SSD::Read(int lba) const { return readCmd.Run(lba, storage); }
unsigned int SSD::Read(ReadArguments &readArgs) {
  readCmd->Run(&readArgs);
  unsigned int readData = dynamic_cast<ReadCmd *>(readCmd)->GetOutputData();
  std::ofstream ofs;
  ofs.open("../SSD/ssd_output.txt");
  ofs << " 0x" + (std::stringstream()
                  << std::hex << std::setw(8) << std::setfill('0') << readData)
                     .str();

  ofs.close();
  return readData;
}

void SSD::Write(IArguments &args) { writeCmd->Run(&args); }
