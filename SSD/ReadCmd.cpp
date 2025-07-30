#include "ReadCmd.h"

#include <filesystem>
#include <fstream>
#include <iostream>

void ReadCmd::Run(ReadArguments *args) {
  outputData = ReadFromSsd(args->GetLba());
}

unsigned int ReadCmd::GetOutputData() const { return outputData; }

bool ReadCmd::DoesFileExist(const std::string &fileName) {
  std::ifstream ifs;
  ifs.open(fileName);
  if (ifs.is_open()) {
    ifs.close();
    return true;
  }
  return false;
}

void ReadCmd::CreateFileOrThrows(const std::string &fileName) {
  std::ofstream ofs;
  ofs.open(fileName);
  if (ofs.is_open()) {
    for (int i = 0; i < 100; i++) ofs << "0x00000000\n";
    ofs.close();
    return;
  }

  throw std::runtime_error("cannot create ssd_nand.txt file.");
}

unsigned int ReadCmd::ReadFromSsd(int reqLba) {
  if (false == DoesFileExist(SSD_NAND_TXT_FILEPATH)) {
    CreateFileOrThrows(SSD_NAND_TXT_FILEPATH);
  }

  std::ifstream ifs(SSD_NAND_TXT_FILEPATH);
  std::string line;
  int lba = 0;
  while (std::getline(ifs, line)) {
    if (lba == reqLba) {
      return stoul(line);
    }
    lba++;
  }
  ifs.close();

  throw std::runtime_error("Invalid LBA");
}
