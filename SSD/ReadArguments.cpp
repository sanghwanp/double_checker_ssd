#include "ReadArguments.h"
ReadArguments::ReadArguments() {}

unsigned int ReadArguments::GetLba() const { return lba; }

std::vector<std::string> ReadArguments::GetTokensAndValidateTokenCount(
    const std::string& cmdStr) {
  std::istringstream iss(cmdStr);
  std::vector<std::string> result;
  std::string token;

  while (iss >> token) {
    result.push_back(token);
  }
  if (result.size() != 2) {
    throw std::invalid_argument("Invalid Arguments: argc must be 2");
  }
  return result;
}

bool ReadArguments::IsCmdTypeReadStr(const std::string& cmdTypeStr) {
  return cmdTypeStr == "R" || cmdTypeStr == "read";
}

void ReadArguments::ParseAndValidate(std::string argsStr) {
  std::vector<std::string> tokens = GetTokensAndValidateTokenCount(argsStr);
  const std::string& cmdTypeStr = tokens.at(0);

  if (IsCmdTypeReadStr(cmdTypeStr)) {
    cmdType = CMD_TYPE_READ;
    const std::string& lbaStr = tokens.at(1);
    lba = std::stoul(lbaStr);
  }

  ValidateArguments();
}

void ReadArguments::ValidateArguments() {
  if (cmdType == CMD_TYPE_READ && lba <= MAX_LBA) return;

  throw std::invalid_argument("Invalid Arguments");
}
