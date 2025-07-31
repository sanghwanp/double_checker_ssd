#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "TestShell.h"

#if (MAIN_SELECT == 3)
int main() {
  TestShell shell;
  return shell.Exec();
}
#endif