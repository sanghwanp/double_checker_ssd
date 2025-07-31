#include "ReadCommand.h"

#include <filesystem>
#include <fstream>
#include <iostream>
//
//unsigned int ReadCmd::Execute(IArguments *args, std::vector<unsigned int> &cache) {
//  LoadFromNandFile(cache);
//  return cache[args->GetLba()];
//}
//
//bool ReadCmd::DoesFileExist(const std::string &fileName) {
//  std::ifstream ifs;
//  ifs.open(fileName);
//  if (ifs.is_open()) {
//    ifs.close();
//    return true;
//  }
//  return false;
//}
//
//void ReadCmd::CreateFile(const std::string &fileName) {
//  std::ofstream ofs;
//  ofs.open(fileName);
//  if (ofs.is_open()) {
//    for (int i = 0; i < SSDConfig::kStorageSize; i++) {
//      ofs << std::hex << SSDConfig::kStorageInitValue << "\n";
//    }
//    ofs.close();
//    return;
//  }
//
//  throw std::runtime_error("cannot create ssd_nand.txt file.");
//}
//
//void ReadCmd::LoadFromNandFile(std::vector<unsigned int> &cache) {
//  if (false == DoesFileExist(SSDConfig::SSD_NAND_TXT_FILEPATH)) {
//    CreateFile(SSDConfig::SSD_NAND_TXT_FILEPATH);
//  }
//
//  std::ifstream ifs(SSDConfig::SSD_NAND_TXT_FILEPATH);
//  for (int idx = 0; idx < SSDConfig::kStorageSize; ++idx) {
//    ifs >> std::hex >> cache[idx];
//  }
//  ifs.close();
//}
