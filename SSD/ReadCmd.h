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
  unsigned int ReadFromFile(int reqLba);
  const std::string NAND_FNAME = "../SSD/ssd_nand.txt";
  unsigned int outputData;
};
