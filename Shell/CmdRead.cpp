#include "CmdRead.h"

#include <iostream>
#include <iomanip>

CommandRead::CommandRead(SSDInterface* ssdInterface) : ssd(ssdInterface) {}

bool CommandRead::Call(IParam& param) {
  ReadParam& readParam = dynamic_cast<ReadParam&>(param);

  unsigned int lba = std::stoi(readParam.lba);
  if (IsInvalidLBA(lba)) {
    // ERROR VALUE: false
    return false;
  }

  std::string value = ssd->Read(lba);

  std::cout << "[Read] LBA " << std::setw(2) << std::setfill('0') << lba << " : "
            << value << "\n";

  // SUCCESS VALUE: true
  return true;
}

bool CommandRead::IsInvalidLBA(unsigned int lba) { return lba > MAX_LBA; }
