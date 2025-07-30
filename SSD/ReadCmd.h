#pragma once
#include <vector>

#include "ReadArguments.h"

#define interface struct
interface ICmd {
  virtual ~ICmd() = default;
  virtual void Run(ReadArguments * args) = 0;
};

class ReadCmd : public ICmd {
 public:
  void Run(ReadArguments *args);
  unsigned int GetOutputData() const;

private:
  unsigned int ReadFromSsd(int reqLba);
  const std::string SSD_NAND_TXT_FILEPATH = "../SSD/ssd_nand.txt";
  unsigned int outputData;

private:
	bool DoesFileExist(const std::string & fileName);
	void CreateFileOrThrows(const std::string &fileName);
};
