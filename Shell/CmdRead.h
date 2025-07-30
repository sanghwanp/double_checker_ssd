#pragma once

#include <string>
#include <vector>

#include "SSDInterface.h"

class CommandRead {
 public:
  CommandRead(SSDInterface* ssdInterface);
  int Call(std::vector<std::string> program);

 private:
  bool IsInvalidLBA(int lba);

  SSDInterface* ssd;
};
