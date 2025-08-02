#include "CmdFullRead.h"

#include <iomanip>
#include <iostream>
#include <sstream>

CommandFullRead::CommandFullRead(SSDInterface* ssdInterface)
    : ssd(ssdInterface) {}

bool CommandFullRead::Call(IParam& param) {
  if (param.eCmd == eInvalidCmd) {
    return false;
  }
  for (unsigned int lba = MIN_LBA; lba <= MAX_LBA; ++lba) {
    std::string value = ssd->Read(lba);

    std::cout << GenerateOutputStr(lba, value);
  }

  // SUCCESS VALUE: true
  return true;
}

std::string CommandFullRead::GenerateOutputStr(unsigned int lba,
                                               std::string value) {
  std::ostringstream oss;
  oss << "[Fullread] LBA " << std::setw(2) << std::setfill('0') << lba << " : "
      << value << "\n";
  return oss.str();
}
