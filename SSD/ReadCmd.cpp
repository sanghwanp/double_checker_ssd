#include "ReadCmd.h"

#include <fstream>
#include <filesystem>
#include <iostream>

void ReadCmd::Run(ReadArguments *args) {
  outputData = ReadFromFile(args->GetLba());
}

unsigned int ReadCmd::GetOutputData() const {
    return outputData;
}

unsigned int ReadCmd::ReadFromFile(int reqLba) {
  std::ifstream ifs;
  ifs.open(NAND_FNAME);
  std::string line;
  int lba=0;
  while(getline(ifs, line)) {
      if(lba == reqLba) {
          return stoul(line);
      }
      lba++;
  }
  ifs.close();

  throw std::runtime_error("Invalid LBA");
}
