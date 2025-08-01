#include "CmdFlush.h"

#include <iostream>

CommandFlush::CommandFlush(SSDInterface* ssdInterface) : ssd(ssdInterface) {}

bool CommandFlush::Call(IParam& param) {
  if (param.eCmd == eInvalidCmd) {
    return false;
  }
  ssd->Flush();
  return true;
}
