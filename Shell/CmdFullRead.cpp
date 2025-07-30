#include "CmdFullRead.h"

#include <iomanip>
#include <iostream>

CommandFullRead::CommandFullRead(SSDInterface* ssdInterface)
    : ssd(ssdInterface) {}

bool CommandFullRead::Call(const std::vector<std::string>& program) {
  // program example:
  // {"fullread"}

  // precondition check
  if (program.size() != PROGRAM_SIZE) {
    // ERROR VALUE: false
    return false;
  }

  if (program[COMMAND_NAME_INDEX] != COMMAND_NAME) {
    // ERROR VALUE: false
    return false;
  }

  for (unsigned int lba = MIN_LBA; lba <= MAX_LBA; ++lba) {
    std::string value = ssd->Read(lba);

    std::cout << "[Fullread] LBA " << std::setw(2) << std::setfill('0') << lba
              << " : " << value << "\n";
  }

  // SUCCESS VALUE: true
  return true;
}
