#include "CmdFlush.h"

#include <iostream>

CommandFlush::CommandFlush(SSDInterface* ssdInterface) : ssd(ssdInterface) {}

bool CommandFlush::Call(const std::vector<std::string>& program) {
  if (program.size() != COMMAND_SIZE) {
    printInvalidCommandMessage();
    return false;
  }
  ssd->Flush();
  return true;
}

void CommandFlush::printInvalidCommandMessage() {
  std::cout << INVALID_COMMAND_MESSAGE;
}
