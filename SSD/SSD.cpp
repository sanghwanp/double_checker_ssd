#include "SSD.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

SSD SSD::instance;

SSD::SSD() {
  if (filedriver.CheckFileExist(STORAGE_FILE_NAME))
    Open();
  else
    Format();
}

void SSD::Format() {
  filedriver.SaveFile(STORAGE_FILE_NAME, storageCache, MAX_STORAGE_IDX);
}

void SSD::Open() {
  filedriver.LoadFile(STORAGE_FILE_NAME, storageCache, MAX_STORAGE_IDX);
}

bool SSD::Run(vector<string> args) {
  IParam *cmd;

  cmd = parser.Parse(args);

  switch (cmd->eCmd) {
    case SSD_CMD::eWriteCmd:
      // Write(cmd);
      break;
    case SSD_CMD::eReadCmd:
      // Read(cmd);
      break;
    case SSD_CMD::eInvalidCmd:

      break;
    default:
      break;
  }

  return false;
}

void SSD::SetWriteCmd(ICmd *cmd) { this->writeCmd = cmd; }

void SSD::SetReadCmd(ICmd *cmd) { this->readCmd = cmd; }

void SSD::SaveToOutputFile(unsigned int readData) {
  std::ofstream ofs;
  ofs.open("C:\\ssd_output.txt");
  ofs << (std::stringstream() << std::hex << readData).str();
  ofs.close();
}

unsigned int SSD::Read(IArguments *args) {
  unsigned int readData = readCmd->Run(args, cache);
  SaveToOutputFile(readData);
  return readData;
}

void SSD::Write(IArguments *args) { writeCmd->Run(args, cache); }

unsigned int SSD::GetCachedData(unsigned int lba) {
  if (lba >= SSDConfig::kStorageSize) {
    throw std::invalid_argument("Invalid LBA access");
  }
  return cache[lba];
}