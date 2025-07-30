#pragma once
#include <vector>
#include <string>

#include "ICmd.h"
#include "ReadArguments.h"
#include "SsdConfig.h"

class ReadCmd : public ICmd {
 public:
  unsigned int Run(IArguments *args, std::vector<unsigned int> &cache) override;

 private:
  void LoadFromNandFile(std::vector<unsigned int> &cache);

  bool DoesFileExist(const std::string &fileName);
  void CreateFile(const std::string &fileName);
};
