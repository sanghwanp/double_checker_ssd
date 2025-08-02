#include "CmdEraseRange.h"

#include <iostream>

#include "logger.h"

CommandEraseRange::CommandEraseRange(SSDInterface* ssdInterface)
    : CommandErase(ssdInterface) {}

bool CommandEraseRange::Call(IParam& param) {
  EraseRangeParam* eraseRangeParam = dynamic_cast<EraseRangeParam*>(&param);
  unsigned int lbaStart = 0;
  unsigned int lbaEnd = 0;
  try {
    lbaStart = std::stoi(eraseRangeParam->lbaStart);
    lbaEnd = std::stoi(eraseRangeParam->lbaEnd);
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


  EraseParam eraseParam(eEraseCmd, std::to_string(lbaStart),
                        std::to_string(size));

  return CommandErase::Call(eraseParam);
}
