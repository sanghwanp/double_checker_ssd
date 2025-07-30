#include "WriteCmd.h"

#include <cstring>
#include <fstream>
#include <iomanip>

void WriteCmd::Run(IArguments* args) {
  auto writeArgs = dynamic_cast<WriteArguments*>(args);
  if (!writeArgs) {
    throw std::invalid_argument("Invalid argument type for WriteCmd");
  }

  LoadFromFile();                                      // 파일 읽기
  SetData(writeArgs->GetLba(), writeArgs->GetCachedData());  // 데이터 설정
  SaveToFile();                                        // 파일에 저장
}

bool WriteCmd::CheckFirst() {
  std::ifstream inFile(SSD_NAND_TXT_FILEPATH);
  return !inFile.is_open();
}

//void WriteCmd::Init() { memset(cache, 0x0, sizeof(cache)); }

void WriteCmd::SetData(int idx, unsigned int data) { cache[idx] = data; }

unsigned int WriteCmd::GetCachedData(int idx) const { return cache[idx]; }

bool WriteCmd::DoesFileExist(const std::string &fileName) {
  std::ifstream ifs;
  ifs.open(fileName);
  if (ifs.is_open()) {
    ifs.close();
    return true;
  }
  return false;
}

void WriteCmd::CreateFile(const std::string &fileName) {
  std::ofstream ofs;
  ofs.open(fileName);
  if (ofs.is_open()) {
    for (int i = 0; i < ReadArguments::LBA_SIZE(); i++) ofs << "0\n";
    ofs.close();
    return;
  }

  throw std::runtime_error("cannot create ssd_nand.txt file.");
}

void WriteCmd::LoadFromFile() {
  if (false == DoesFileExist(SSD_NAND_TXT_FILEPATH)) {
    CreateFile(SSD_NAND_TXT_FILEPATH);
  }

  std::ifstream ifs(SSD_NAND_TXT_FILEPATH);
  for (int idx = 0; idx < MAX_LBA_SIZE; ++idx) {
    ifs >> std::hex >> cache[idx];
  }
  ifs.close();
}

void WriteCmd::SaveToFile() {
  std::ofstream ofs(SSD_NAND_TXT_FILEPATH);
  if (!ofs.is_open()) {
    throw std::runtime_error("Failed to open SSD file for writing");
  }

  for (int idx = 0; idx < MAX_LBA_SIZE; ++idx) {
    ofs << std::hex << cache[idx] << "\n";
  }
  ofs.close();
}
