#pragma once
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#define interface struct

class ReadArguments {
  enum CmdType { CMD_TYPE_OTHER, CMD_TYPE_WRITE, CMD_TYPE_READ };

 public:
  ReadArguments();
  virtual ~ReadArguments() = default;

 public:
  unsigned int GetLba() const;
  void Parse(std::string cmdStr);
  bool CheckErrorCmd();

 private:
  CmdType cmdType = CMD_TYPE_OTHER;  // 2: ReadCmdType
  unsigned int lba;
  const unsigned int MAX_LBA = 99;
};
