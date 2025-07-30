#include "CmdRead.h"

#include <iostream>

CommandRead::CommandRead(SSDInterface* ssdInterface) : ssd(ssdInterface) {}

int CommandRead::Call(std::vector<std::string> program) {
  // program example:
  // {"read", 1}

  // precondition check
  if (program.size() != 2) {
    return -1;
  }

  int lba = std::stoi(program[1]);
  std::string value = ssd->Read(lba);

  std::cout << "[READ] LBA " << lba << " : " << value << "\n";
  return 0;
}
