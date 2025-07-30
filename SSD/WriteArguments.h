#pragma once
#include <string>

#include "IArguments.h"

class WriteArguments : public IArguments {
 public:
  unsigned int GetLba() const override;
  unsigned int GetData() const;
  void Parse(const std::string& cmdStr) override;

 private:
  unsigned int lba;
  unsigned int data;
  std::string dataStr;
  static constexpr unsigned int MAX_LBA = 99;
  static constexpr unsigned int MAX_DATA_LEN = 10;
};
