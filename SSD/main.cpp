#if (MAIN_SELECT == 1)

#include "SSD.h"

int main(int argc, char* argv[]) {
  int ret = false;

  std::vector<std::string> args;

  for (int i = 1; i < argc; i++) {
    args.emplace_back(argv[i]);
  }

  SSD::GetInstance().Run(args);

}

#endif