#pragma once
// #include "Parser.h"
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

struct CommandStruct {
  string commandName;
  string firstNumber;
  string secondNumber;
};

class Parser {
 public:
  std::vector<std::string> SplitArgs(const std::string& input);
  CommandStruct Parse(const std::string& input);
  bool CheckTokensStruct(const vector<std::string>& tokens,
                         const string& lastToken);
  bool IsNumberOrHex(const std::string& str);
  bool IsNumber(const std::string& str);
  bool IsHex(const std::string& str);
};