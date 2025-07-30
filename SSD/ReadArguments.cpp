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

void ReadArguments::ParseAndValidate(std::string argsStr) {
  std::vector<std::string> tokens = GetTokensAndValidateTokenCount(argsStr);
  const std::string& typeStr = tokens[0];

  if (typeStr == "R" || typeStr == "read") {
    cmdType = CMD_TYPE_READ;
    const std::string& lbaStr = tokens[1];
    lba = std::stoul(lbaStr);
  }

  if (CheckErrorCmd()) {
    throw std::invalid_argument("Invalid Arguments");
  }
}

bool ReadArguments::CheckErrorCmd() {
  if (cmdType != CMD_TYPE_READ) return true;
  if (lba > MAX_LBA) return true;
  return false;
}
