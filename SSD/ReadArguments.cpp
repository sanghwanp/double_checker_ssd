#include "ReadArguments.h"
unsigned int ReadArguments::LBA_SIZE() { return 100; }

ReadArguments::ReadArguments() {}

unsigned int ReadArguments::GetLba() const { return lba; }

ReadArguments::CmdType ReadArguments::GetCmdType(
    const std::string& cmdTypeStr) {
  if (cmdTypeStr == "R" || cmdTypeStr == "read") {
    return CMD_TYPE_READ;
  }

  return CMD_TYPE_OTHER;
}

std::vector<std::string> ReadArguments::GetTokens(const std::string& cmdStr) {
  std::istringstream iss(cmdStr);
  std::vector<std::string> result;
  std::string token;

  while (iss >> token) {
    result.push_back(token);
  }
  return result;
}

void ReadArguments::Parse(const std::string& argsStr) {
  std::vector<std::string> tokens = GetTokens(argsStr);
  ValidateTokenCount(tokens);

  const std::string& cmdTypeStr = tokens.at(0);
  cmdType = GetCmdType(cmdTypeStr);
  ValidateCmdTypeRead(cmdType);

  const std::string& lbaStr = tokens.at(1);
  lba = std::stoul(lbaStr);
  ValidateLba(lba);
}

void ReadArguments::ValidateTokenCount(const std::vector<std::string>& tokens) {
  if (tokens.size() == VALID_READ_ARGS_COUNT) return;
  throw std::invalid_argument("Invalid Arguments: argc must be 2");
}

void ReadArguments::ValidateCmdTypeRead(CmdType cmdType) {
  if (cmdType == CMD_TYPE_OTHER) {
    throw std::invalid_argument("Invalid Arguments: Wrong CMD TYPE");
  }
}

void ReadArguments::ValidateLba(int lba) {
  if (lba >= LBA_SIZE()) {
    throw std::invalid_argument("Invalid Arguments: LBA - out of bound");
  }
}
