#if (MAIN_SELECT == 1)
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "ReadArguments.h"
#include "ReadCmd.h"
#include "SSD.h"
#include "WriteArguments.h"
#include "WriteCmd.h"

int main(int argc, char* argv[]) {
  int ret = false;

  std::vector<std::string> args;

  for (int i = 1; i < argc; i++) {
    args.emplace_back(argv[i]);
  }

  return SSD::GetInstance().Run(args);
}

#endif