#include "ReadArguments.h"
ReadArguments::ReadArguments() {}

unsigned int ReadArguments::GetLba() const { return lba; }

std::vector<std::string> ReadArguments::GetTokens(const std::string& cmdStr) {
  std::istringstream iss(cmdStr);
  std::vector<std::string> result;
  std::string token;

  while (iss >> token) {
    result.push_back(token);
  }
  return result;
}

void ReadArguments::ParseOrThrows(std::string argsStr) {
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
  if (tokens.size() == 2U) return;
  throw std::invalid_argument("Invalid Arguments: argc must be 2");
}

void ReadArguments::ValidateCmdTypeRead(CmdType cmdType) {
  if (cmdType == CMD_TYPE_OTHER) {
    throw std::invalid_argument("Invalid Arguments: Wrong CMD TYPE");
  }
}

void ReadArguments::ValidateLba(int lba) {
  if (lba > MAX_LBA) {
    throw std::invalid_argument("Invalid Arguments: LBA - out of bound");
  }
}
