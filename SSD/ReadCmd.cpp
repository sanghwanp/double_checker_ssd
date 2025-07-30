#include "ReadCmd.h"

#include <filesystem>
#include <fstream>
#include <iostream>

unsigned int ReadCmd::Run(IArguments *args, std::vector<unsigned int> &cache) {
  LoadFromNandFile(cache);
  return cache[args->GetLba()];
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
    for (int i = 0; i < SsdConfig::kStorageSize; i++) {
      ofs << std::hex << SsdConfig::kStorageInitValue << "\n";
    }
    ofs.close();
    return;
  }

  throw std::runtime_error("cannot create ssd_nand.txt file.");
}

void ReadCmd::LoadFromNandFile(std::vector<unsigned int> &cache) {
  if (false == DoesFileExist(SsdConfig::SSD_NAND_TXT_FILEPATH)) {
    CreateFile(SsdConfig::SSD_NAND_TXT_FILEPATH);
  }

  std::ifstream ifs(SsdConfig::SSD_NAND_TXT_FILEPATH);
  for (int idx = 0; idx < SsdConfig::kStorageSize; ++idx) {
    ifs >> std::hex >> cache[idx];
  }
  ifs.close();
}
