#pragma once

#include "Parser.h"
#include "MockSSD.h"
#include "RealSSD.h"
#include "CmdWrite.h"
#include "CmdRead.h"
#include "CmdFullWrite.h"
#include "CmdFullRead.h"
#include "CmdExit.h"
#include "CmdHelp.h"
#include "CmdErase.h"
#include "CmdFlush.h"
#include "CmdTestScript.h"

class TestShell {
 public:
  int Exec(void);

 private:
  int parseAndExecCommand(std ::string command);
  Parser parser;

  #ifdef UNIT_TEST
  MockSSD ssdDriver;
  #else
  RealSSD ssdDriver;
  #endif
  CommandWrite commandWrite{&ssdDriver};
  CommandRead commandRead{&ssdDriver};
  CommandFullWrite commandFullWrite{&ssdDriver};
  CommandFullRead commandFullRead{&ssdDriver};
  CommandExit commandExit;
  CommandHelp commandHelp;
  CommandErase commandErase{&ssdDriver};
  CommandFlush commandFlush{&ssdDriver};
  CommandTestScript commandTestScript{&ssdDriver};
};
