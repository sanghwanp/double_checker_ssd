#pragma once
#include <vector>

#include "ICmd.h"
#include "ReadArguments.h"

class ReadCmd : public ICmd {
 public:
  void Run(IArguments *args) override;
  unsigned int GetReadResult() const;

 private:
  unsigned int readResult;
  static constexpr int MAX_LBA_SIZE = 100;
  unsigned int cache[MAX_LBA_SIZE]{};
  const std::string SSD_NAND_TXT_FILEPATH = "C:\\ssd_nand.txt";

 private:
  unsigned int GetCachedData(int lba) const;
  void LoadFromFile();

  bool DoesFileExist(const std::string &fileName);
  void CreateFile(const std::string &fileName);
};
