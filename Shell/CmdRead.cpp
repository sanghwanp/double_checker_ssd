#include "CmdRead.h"

#include <iostream>

CommandRead::CommandRead(SSDInterface* ssdInterface) : ssd(ssdInterface) {}

int CommandRead::Call(std::vector<std::string> program) {
  // program example:
  // {"read", 1}

  // precondition check
  if (program.size() != 2) {
    // ERROR VALUE: 1
    return 1;
  }

  int lba = std::stoi(program[1]);
  if (IsInvalidLBA(lba)) {
    return 1;
  }

  std::string value = ssd->Read(lba);

  std::cout << "[Read] LBA " << lba << " : " << value << "\n";

  // SUCCESS VALUE: 0
  return 0;
}

bool CommandRead::IsInvalidLBA(int lba) { return lba < 0 || lba >= 100; }
