#pragma once

#include "Parser.h"
#include "MockSSD.h"
#include "CmdWrite.h"
#include "CmdRead.h"
#include "CmdFullWrite.h"
#include "CmdFullRead.h"
#include "CmdExit.h"
#include "CmdHelp.h"

class TestShell {
 public:
  int Exec(void);

 private:
  int parseAndExecCommand(std ::string command);
  Parser parser;

  MockSSD ssdDriver;
  CommandWrite commandWrite{&ssdDriver};
  CommandRead commandRead{&ssdDriver};
  CommandFullWrite commandFullWrite{&ssdDriver};
  CommandFullRead commandFullRead{&ssdDriver};
  CommandExit commandExit;
  CommandHelp commandHelp;
};
