#include "CmdEraseRange.h"

#include <iostream>

#include "logger.h"

CommandEraseRange::CommandEraseRange(SSDInterface* ssdInterface)
    : CommandErase(ssdInterface) {}

bool CommandEraseRange::Call(const std::vector<std::string>& program) {
  // program example:
  // {"erase_range", "5", "20"}
  // {"erase_range", "60", "40"}
  // {"erase_range", "0", "99"}

  // precondition check
  if (program.size() != PROGRAM_SIZE) {
    // ERROR
    return false;
  }

  unsigned int lbaStart;
  unsigned int lbaEnd;
  try {
    lbaStart = std::stoi(program[LBA_START_INDEX]);
    lbaEnd = std::stoi(program[LBA_END_INDEX]);
  } catch (...) {
    // ERROR
    return false;
  }

  if (IsInvalidLBA(lbaStart) || IsInvalidLBA(lbaEnd)) {
    // ERROR
    return false;
  }

  int size =
      (lbaStart <= lbaEnd) ? lbaEnd - lbaStart + 1 : lbaEnd - lbaStart - 1;


  std::vector<std::string> eraseProgram = {"erase",
                                           std::to_string(lbaStart),
                                           std::to_string(size)};

  return CommandErase::Call(eraseProgram);
}
