#pragma once
#include <string>
enum class CmdType { WRITE, ERASE };
class Interval {
 public:
  int s, e;
  unsigned long long data;
  CmdType cmdType;  // 0: Write, 1: Erase

  Interval(unsigned int s, unsigned int e, unsigned long long data,
           CmdType cmdType = CmdType::WRITE);

  int Length() const;

  std::string ToString(CmdType cmdType) const;
  void Print() const;
};
