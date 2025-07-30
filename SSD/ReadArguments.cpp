#include "ReadArguments.h"

ReadArguments::ReadArguments() {}

unsigned int ReadArguments::GetLba() const { return lba; }

void ReadArguments::Parse(std::string cmdStr) {
  std::istringstream iss(cmdStr);

  std::vector<std::string> tokens;
  std::string token;
  while (iss >> token) {
    tokens.push_back(token);
  }
  if (tokens.size() != 2) {
    throw std::invalid_argument("Invalid Arguments: argc must be 2");
  }
  std::string typeStr = tokens[0];

  if (typeStr == "R" || typeStr == "read") {
    cmdType = CMD_TYPE_READ;
    std::string lbaStr = tokens[1];
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
