#include "WriteCommand.h"

#include <cstring>
#include <fstream>
#include <iomanip>
//
//unsigned int WriteCommand::Execute(IArguments* args, std::vector<unsigned int>& cache) {
//  WriteArguments* writeArgs = dynamic_cast<WriteArguments*>(args);
//  if (!writeArgs) {
//    throw std::invalid_argument("Invalid argument type for WriteCmd");
//  }
//
//  LoadFromNandFile(cache);
//  SetData(cache, writeArgs);
//  SaveToFile(cache);
//
//  const int kVoidResult = 0;
//  return kVoidResult;
//}
//
//bool WriteCommand::CheckFirst() {
//  std::ifstream ifs(SSDConfig::SSD_NAND_TXT_FILEPATH);
//  return !ifs.is_open();
//}
//
//void WriteCommand::SetData(std::vector<unsigned int>& cache,
//                       WriteArguments* writeArgs) {
//  cache[writeArgs->GetLba()] = writeArgs->GetCachedData();
//}
//
//bool WriteCommand::DoesFileExist(const std::string& fileName) {
//  std::ifstream ifs;
//  ifs.open(fileName);
//  if (ifs.is_open()) {
//    ifs.close();
//    return true;
//  }
//  return false;
//}
//
//void WriteCommand::CreateFile(const std::string& fileName) {
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
//void WriteCommand::LoadFromNandFile(std::vector<unsigned int>& cache) {
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
//
//void WriteCommand::SaveToFile(std::vector<unsigned int>& cache) {
//  std::ofstream ofs(SSDConfig::SSD_NAND_TXT_FILEPATH);
//  if (!ofs.is_open()) {
//    throw std::runtime_error("Failed to open SSD file for writing");
//  }
//
//  for (int idx = 0; idx < SSDConfig::kStorageSize; ++idx) {
//    ofs << std::hex << cache[idx] << "\n";
//  }
//  ofs.close();
//}
