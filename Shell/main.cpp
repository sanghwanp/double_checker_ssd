#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "ScriptRunner.h"
#include "TestShell.h"

int main(int argc, char* argv[]) {
  if (argc == 2) {
    RealSSD realSsd("ssd.exe", "ssd_output.txt");
    ScriptRunner runner(&realSsd, argv[1]);
    runner.Run();

    return 0;
  }

  TestShell shell;
  return shell.Exec();
}
