#include "CmdRead.h"

#include <iostream>

CommandRead::CommandRead(SSDInterface* ssdInterface) : ssd(ssdInterface) {}

bool CommandRead::Call(const std::vector<std::string>& program) {
  // program example:
  // {"read", 1}

  // precondition check
  if (program.size() != PROGRAM_SIZE) {
    // ERROR VALUE: false
    return false;
  }

  unsigned int lba = std::stoi(program[LBA_INDEX]);
  if (IsInvalidLBA(lba)) {
    // ERROR VALUE: false
    return false;
  }

  std::string value = ssd->Read(lba);

  std::cout << "[Read] LBA " << lba << " : " << value << "\n";

  // SUCCESS VALUE: true
  return true;
}

bool CommandRead::IsInvalidLBA(unsigned int lba) { return lba > MAX_LBA; }
