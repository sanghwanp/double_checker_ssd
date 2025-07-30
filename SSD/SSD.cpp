#include "SSD.h"
#include "ICommand.h"
#include <cctype>
#include <fstream>
#include <iomanip>
#include <sstream>

void SSD::Run(std::string input) {
  if (IsValidArgs(input) == false) {
    std::cout << "ERROR" << std::endl;
    return;
  }

  args = Parse(input);

  switch (args.cmdType) {
    case CMD_READ:
        // read.run()
      break;
    case CMD_WRITE:
        // write.run()
      break;
    default:
      break;
  }
}

CommandArguments SSD::Parse(std::string cmdStr) {
  
}

bool CommandArguments::IsValidArgs(std::string cmdStr) {
  std::istringstream iss(cmdStr);
  std::string typeStr;
  std::string lbaStr;
  std::string dataStr;
  CommandArguments arg;
  iss >> typeStr >> lbaStr >> dataStr;

  // 1. Cmd Type check
  if (typeStr[0] == 'W' || typeStr[0] == 'w') {
    return true;
  }

  uint lba = std::stoul(lbaStr);
  if (lba < 0 || lba >= MAX_LBA_SIZE) {
    return true;
  }

  if (dataStr.length() > MAX_DATA_LEN) {
    return true;
  }
  if (!(dataStr[0] == '0' && dataStr[1] == 'x')) {
    return true;
  }
  for (int i = 2; i < dataStr.length(); i++) {
    if (std::isxdigit(dataStr[i])) continue;
    return true;
  }
  return false;
}