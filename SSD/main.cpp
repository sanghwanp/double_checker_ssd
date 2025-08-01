

#include "SSD.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> args;

  for (int i = 1; i < argc; i++) {
    args.emplace_back(argv[i]);
  }

  SSD::GetInstance().Run(args);
  return 0;
}
