#pragma once
#include <string>

#include "IParam.h"

class WriteArguments : public IArguments {
public:
  static unsigned int LBA_SIZE();
  static unsigned int MAX_DATA_LEN();

 public:
  unsigned int GetLba() const override;
  unsigned int GetCachedData() const;
  void Parse(const std::string& cmdStr) override;

 private:
  unsigned int lba;
  unsigned int data;
  std::string dataStr;
};
