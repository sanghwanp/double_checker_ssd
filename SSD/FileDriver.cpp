#include "FileDriver.h"

bool FileDriver::CheckFileExist(const char* filename) {
  std::ifstream ifs(filename);
  return ifs.is_open();
}

void FileDriver::LoadFile(const char* filename, unsigned int* data, size_t size) {
  std::ifstream ifs(filename);

  std::string line;
  size_t idx = 0;

  while (std::getline(ifs, line) && idx < size) {
    data[idx] = std::stoul(line, nullptr, 16);
    ++idx;
  }

  ifs.close();
}

void FileDriver::SaveFile(const char* filename, const unsigned int* data, size_t size) {
  std::ofstream ofs(filename);

  for (size_t i = 0; i < size; ++i) {
    ofs << "0x" << std::hex << std::uppercase << std::setw(8)
        << std::setfill('0') << data[i] << "\n";
  }

  ofs.close();
}