#pragma once
#include <sstream>
#include <string>
#define interface struct

class ReadArguments {
 public:
  int cmdType=CMD_TYPE_OTHER;  // 2: ReadCmdType
  int lba;
  std::istringstream iss;

  virtual ~ReadArguments() = default;
  void Parse(std::string cmdStr) {
    std::string typeStr;
    iss = std::istringstream(cmdStr);
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
  const int MAX_LBA = 99;
  const int CMD_TYPE_OTHER=0, CMD_TYPE_WRITE=1, CMD_TYPE_READ=2;
};
