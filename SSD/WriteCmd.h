#pragma once
#include <string>
#include <vector>

#include "ICmd.h"
#include "SsdConfig.h"
#include "WriteArguments.h"

class WriteCmd : public ICmd {
 public:
  unsigned int Run(IArguments* args, std::vector<unsigned int>& cache) override;

  bool CheckFirst();
  void SetData(std::vector<unsigned int>& cache, WriteArguments* writeArgs);

 private:
  void LoadFromNandFile(std::vector<unsigned int>& cache);
  void SaveToFile(std::vector<unsigned int>& cache);

  bool DoesFileExist(const std::string& fileName);
  void CreateFile(const std::string& fileName);
};
