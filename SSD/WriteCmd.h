#pragma once
#include <string>

#include "ICmd.h"
#include "WriteArguments.h"

class WriteCmd : public ICmd {
 public:
  void Run(IArguments* args) override;

  bool CheckFirst();
  //void Init();
  void SetData(int idx, unsigned int data);
  unsigned int GetCachedData(int idx) const;

 private:
  static constexpr int MAX_LBA_SIZE = 100;
  unsigned int cache[MAX_LBA_SIZE]{};
  const std::string SSD_NAND_TXT_FILEPATH = "C:\\ssd_nand.txt";

 private:
  void LoadFromFile();
  void SaveToFile();

  bool DoesFileExist(const std::string &fileName);
  void CreateFile(const std::string &fileName);
};
