#pragma once
#include <vector>

#include "ICmd.h"
#include "ReadArguments.h"

class ReadCmd : public ICmd {
 public:
  void Run(IArguments *args) override;
  unsigned int GetOutputData() const;

 private:
  unsigned int ReadFromSsd(int reqLba);
  const std::string SSD_NAND_TXT_FILEPATH = "C:\\ssd_nand.txt";
  unsigned int outputData;
  // const int LBA_SIZE = 100;

 private:
  bool DoesFileExist(const std::string &fileName);
  void CreateFile(const std::string &fileName);
};
