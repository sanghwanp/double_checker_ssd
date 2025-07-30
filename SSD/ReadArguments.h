#pragma once
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

#include "IArguments.h"

class ReadArguments : public IArguments {
  enum CmdType { CMD_TYPE_OTHER, CMD_TYPE_WRITE, CMD_TYPE_READ };

 public:
  ReadArguments();
  virtual ~ReadArguments() = default;

 public:
  static unsigned int LBA_SIZE();

 public:
  unsigned int GetLba() const;
  void Parse(const std::string &cmdStr);

 private:
  CmdType cmdType = CMD_TYPE_OTHER;  // 2: ReadCmdType
  unsigned int lba;
  const unsigned int VALID_READ_ARGS_COUNT = 2U;

 private:
  std::vector<std::string> GetTokens(const std::string &cmdStr);
  CmdType GetCmdType(const std::string &cmdTypeStr);

  void ValidateTokenCount(const std::vector<std::string> &tokens);
  void ValidateCmdTypeRead(CmdType cmdType);
  void ValidateLba(int lba);
};
