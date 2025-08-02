#pragma once
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

#include "SSDConfig.h"
#include "Types.h"

class FileDriver {
 public:
  FileDriver();
  static FileDriver* GetInstance() {
    static FileDriver instance;
    return &instance;
  }
  void Init();
  bool CheckFileExist(const char* filename);
  void LoadData();
  void StoreData();
  void StoreOutput(unsigned int val);
  void StoreError();

  const unsigned int* GetBufferAddr(unsigned int lba = 0);
  const unsigned int GetBufferData(unsigned int lba);
  void SetBufferData(unsigned int lba, unsigned int data);

 private:
  unsigned int storageCache[MAX_STORAGE_IDX] = {0};
};
