#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "ILogger.h"
#include "MockSSD.h"
#include "RealSSD.h"
#include "ScriptRunner.h"
#include "TestShell.h"

int main(int argc, char* argv[]) {
#ifdef UNIT_TEST
  MockSSD realSsd("ssd.exe", "ssd_output.txt");
#else
  RealSSD realSsd("ssd.exe", "ssd_output.txt");
#endif

  if (argc == 2) {
    ILogger::GetInstance()->SetConsoleOutput(false);
    ScriptRunner runner(&realSsd, argv[1]);
    runner.Run();

    return 0;
  }

  TestShell shell(&realSsd);
  return shell.Exec();
}
