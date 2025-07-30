#pragma once
#include <cstring>
#include <fstream>
#include <iomanip>

#include "ICmd.h"
#include "WriteArguments.h"

class WriteCmd : public ICmd {
 public:
  void Run(IArguments* args) override;

  bool CheckFirst();
  void Init();
  void SetData(int idx, unsigned int data);
  unsigned int GetData(int idx) const;

 private:
  static constexpr int MAX_LBA_SIZE = 100;
  unsigned int nand[MAX_LBA_SIZE]{};
  const std::string FILE_NAME = "ssd_nand.txt";

 private:
  void LoadFromFile();
  void SaveToFile();
};
