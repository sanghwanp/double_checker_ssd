#include "FileDriver.h"

FileDriver::FileDriver() { Init(); }

void FileDriver::Init() {
  if (CheckFileExist(STORAGE_FILE_NAME))
    LoadFile(STORAGE_FILE_NAME, storageCache, MAX_STORAGE_IDX);
  else
    SaveFile(STORAGE_FILE_NAME, storageCache, MAX_STORAGE_IDX);
}
bool FileDriver::CheckFileExist(const char* filename) {
  std::ifstream ifs(filename);
  return ifs.is_open();
}

void FileDriver::LoadFile(const char* filename, unsigned int* data,
                          size_t size) {
  std::ifstream ifs(filename);

  std::string line;
  size_t idx = 0;

  while (std::getline(ifs, line) && idx < size) {
    data[idx] = std::stoul(line, nullptr, 16);
    ++idx;
  }

  ifs.close();
}

void FileDriver::SaveFile(const char* filename, const unsigned int* data,
                          size_t size) {
  std::ofstream ofs(filename);

  for (size_t i = 0; i < size; ++i) {
    ofs << "0x" << std::hex << std::uppercase << std::setw(8)
        << std::setfill('0') << data[i] << "\n";
  }

  ofs.close();
}

void FileDriver::SaveFile(const char* filename, const std::string& message) {
  std::ofstream ofs(filename);
  ofs << message << "\n";
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
