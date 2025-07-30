#pragma once
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#define interface struct

class ReadArguments {
  enum CmdType { CMD_TYPE_OTHER, CMD_TYPE_WRITE, CMD_TYPE_READ };

 public:
  int GetLba() const { return lba; }

  virtual ~ReadArguments() = default;
  void Parse(std::string cmdStr) {
    std::istringstream iss(cmdStr);

    std::vector<std::string> tokens;
    std::string token;
    while(iss >> token) {
        tokens.push_back(token);
    }
    if(tokens.size()!=2) {
        throw std::invalid_argument("Invalid Arguments: argc must be 2");
    }
    std::string typeStr = tokens[0];

    if (typeStr == "R" || typeStr == "read") {
      cmdType = CMD_TYPE_READ;
      std::string lbaStr = tokens[1];
      lba = std::stoi(lbaStr);
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
