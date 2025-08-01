#include "Interval.h"

Interval::Interval(unsigned int s, unsigned int e, unsigned long long data,
                   CmdType cmdType)
    : s(s), e(e), data(data), cmdType(cmdType) {}

int Interval::Length() const { return e - s + 1; }

std::string Interval::ToString(CmdType cmdType) const {
  if (cmdType == CmdType::WRITE)
    return "WRITE";
  else if (cmdType == CmdType::ERASE)
    return "ERASE";
  else
    return "NOTHING";
}

void Interval::Print() const {
  printf("[%d,%d]->val:%llu, cmdType:%s\n", s, e, data,
         ToString(cmdType).c_str());
}
