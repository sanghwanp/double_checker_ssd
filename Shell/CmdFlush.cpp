#include "CmdFlush.h"

#include <iostream>

CommandFlush::CommandFlush(SSDInterface* ssdInterface)
    : ssd(ssdInterface) {}

bool CommandFlush::Call(const std::vector<std::string>& program) {
  if (program.size() != 1) {
    printInvalidCommandMessage();
    return false;
  } 
   ssd->Flush();
}

void CommandFlush::printInvalidCommandMessage() {
  std::cout << INVALID_COMMAND_MESSAGE;
}
