#pragma once
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

class FileDriver {
 public:
  bool CheckFileExist(const char* filename);
  void LoadFile(const char* filename, unsigned int* data, size_t size);
  void SaveFile(const char* filename, const unsigned int* data, size_t size);
};