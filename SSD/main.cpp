#include "SSD.h"

#if (MAIN_SELECT == 1)
int main(int argc, char* argv[]) {
  std::string input;

  std::getline(std::cin, input);

  SSD.Run(input);


  return 0;
}
#endif