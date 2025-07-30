#include "ReadCmd.h"

#include <filesystem>
#include <fstream>
#include <iostream>

unsigned int ReadCmd::Run(IArguments *args) {
  LoadFromFile();
  return GetCachedData(args->GetLba());
}

bool ReadCmd::DoesFileExist(const std::string &fileName) {
  std::ifstream ifs;
  ifs.open(fileName);
  if (ifs.is_open()) {
    ifs.close();
    return true;
  }
  return false;
}

void ReadCmd::CreateFile(const std::string &fileName) {
  std::ofstream ofs;
  ofs.open(fileName);
  if (ofs.is_open()) {
    for (int i = 0; i < ReadArguments::LBA_SIZE(); i++) ofs << "0\n";
    ofs.close();
    return;
  }

  throw std::runtime_error("cannot create ssd_nand.txt file.");
}

unsigned int ReadCmd::GetCachedData(int lba) const { return cache[lba]; }

void ReadCmd::LoadFromFile() {
  if (false == DoesFileExist(SSD_NAND_TXT_FILEPATH)) {
    CreateFile(SSD_NAND_TXT_FILEPATH);
  }

  std::ifstream ifs(SSD_NAND_TXT_FILEPATH);
  for (int idx = 0; idx < MAX_LBA_SIZE; ++idx) {
    ifs >> std::hex >> cache[idx];
  }
  ifs.close();
}
