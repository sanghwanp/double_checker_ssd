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

bool SSD::Run(std::vector<std::string> args) {
  if (args.size() <= 1 || args.size() >= 4) {
    throw std::invalid_argument("Usage1: R <LBA>\nUsage2: W <LBA> <Data>");
  }

  const std::string &cmdTypeStr = args[0];
  std::string argsStr;
  for (int i = 0; i < args.size(); i++) {
    argsStr += args[i];
    if (i != args.size() - 1) argsStr += " ";
  }

  ReadCmd readCmd;
  WriteCmd writeCmd;

  SetReadCmd(&readCmd);
  SetWriteCmd(&writeCmd);

  if (cmdTypeStr == "R" || cmdTypeStr == "read") {
    ReadArguments readArgs;
    readArgs.Parse(argsStr);
    unsigned int result = Read(&readArgs);

  } else if (cmdTypeStr == "W" || cmdTypeStr == "write") {
    WriteArguments writeArgs;
    writeArgs.Parse(argsStr);

    Write(&writeArgs);
  } else {
    throw std::invalid_argument("Unknown command type");  // ERROR
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
