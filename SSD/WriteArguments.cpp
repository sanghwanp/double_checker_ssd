#include "WriteArguments.h"

#include <iomanip>
#include <sstream>

unsigned int WriteArguments::LBA_SIZE() { return 100; }
unsigned int WriteArguments::MAX_DATA_LEN() { return 10; }

unsigned int WriteArguments::GetLba() const { return lba; }

unsigned int WriteArguments::GetCachedData() const { return data; }

void WriteArguments::Parse(const std::string &cmdStr) {
  std::istringstream iss(cmdStr);
  std::string cmdType;
  iss >> cmdType >> lba >> dataStr;

  if (cmdType != "W" && cmdType != "write") {
    throw std::invalid_argument("Invalid Command Type");
  }

  if (lba >= LBA_SIZE()) {
    throw std::invalid_argument("LBA out of range");
  }

  if (dataStr.size() > MAX_DATA_LEN() || dataStr.substr(0, 2) != "0x") {
    throw std::invalid_argument("Invalid Data Format");
  }

  data = std::stoul(dataStr, nullptr, 16);
}
