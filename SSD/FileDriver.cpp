#include "FileDriver.h"

FileDriver::FileDriver() { Init(); }

void FileDriver::Init() {
  if (CheckFileExist(STORAGE_FILE_NAME))
    LoadData();
  else
    StoreData();
}
bool FileDriver::CheckFileExist(const char* filename) {
  std::ifstream ifs(filename);
  return ifs.is_open();
}

void FileDriver::LoadData() {
  std::ifstream ifs(STORAGE_FILE_NAME);

  std::string line;
  size_t idx = 0;

  while (std::getline(ifs, line) && idx < MAX_STORAGE_IDX) {
    storageCache[idx] = std::stoul(line, nullptr, 16);
    ++idx;
  }

  ifs.close();
}

void FileDriver::StoreData() {
  std::ofstream ofs(STORAGE_FILE_NAME);

  for (size_t i = 0; i < MAX_STORAGE_IDX; ++i) {
    ofs << "0x" << std::hex << std::uppercase << std::setw(8)
        << std::setfill('0') << storageCache[i] << "\n";
  }

  ofs.close();
}

void FileDriver::StoreOutput(unsigned int val) {
  std::ofstream ofs(OUTPUT_FILE_NAME);
  ofs << "0x" << std::hex << std::uppercase << std::setw(8) << std::setfill('0')
      << val;
  ofs.close();
}

void FileDriver::StoreError() {
  std::ofstream ofs(OUTPUT_FILE_NAME);
  ofs << "ERROR" << "\n";
  ofs.close();
}

const unsigned int* FileDriver::GetBufferAddr(unsigned int lba) {
  return &storageCache[lba];
}

const unsigned int FileDriver::GetBufferData(unsigned int lba) {
  return storageCache[lba];
}

void FileDriver::SetBufferData(unsigned int lba, unsigned int data) {
  storageCache[lba] = data;
}
