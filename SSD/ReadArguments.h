#pragma once
#include <sstream>
#include <string>
#define interface struct

class ReadArguments {
  enum CmdType { CMD_TYPE_OTHER, CMD_TYPE_WRITE, CMD_TYPE_READ };

 public:
  int GetLba() const { return lba; }

  virtual ~ReadArguments() = default;
  void Parse(std::string cmdStr) {
    std::string typeStr;
    std::istringstream iss(cmdStr);
    iss >> typeStr;

    if (typeStr == "R" || typeStr == "read") {
      cmdType = CMD_TYPE_READ;
      iss >> lba;
    }

    if (CheckErrorCmd()) {
      throw std::invalid_argument("Invalid Arguments");
    }
  }

  bool CheckErrorCmd() {
    if (cmdType != CMD_TYPE_READ) return true;
    if (lba < 0 || lba > MAX_LBA) return true;
    return false;
  }

  ReadArguments() {}

 private:
  CmdType cmdType = CMD_TYPE_OTHER;  // 2: ReadCmdType
  int lba;

  const int MAX_LBA = 99;
};
