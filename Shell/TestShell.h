#pragma once

#include "Parser.h"

class TestShell {
 public:
  int Exec(void);

 private:
  int parseAndExecCommand(std ::string command);
  Parser parser;
};
