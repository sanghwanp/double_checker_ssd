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
  CmdType GetCmdType(const std::string &cmdTypeStr) {
    if (cmdTypeStr == "R" || cmdTypeStr == "read") {
      return CMD_TYPE_READ;
    }

    return CMD_TYPE_OTHER;
  }
  void ParseOrThrows(std::string cmdStr);
  void ValidateTokenCount(const std::vector<std::string> &tokens);
  void ValidateCmdTypeRead(CmdType cmdType);
  void ValidateLba(int lba);
  std::vector<std::string> GetTokens(const std::string &cmdStr);

 private:
  CmdType cmdType = CMD_TYPE_OTHER;  // 2: ReadCmdType
  unsigned int lba;
  const unsigned int MAX_LBA = 99;
};
