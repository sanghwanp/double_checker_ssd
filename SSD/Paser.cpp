#include <cctype>
#include <iostream>
#include <regex>

#include "Parser.h"

IParam* Parser::GenCommandParam(vector<string> tokens) {
  auto it = commandParamSpecs.find(tokens[0]);
  if (it == commandParamSpecs.end()) return GetInvalidCommand();
  return it->second.paramObj(tokens);
}

IParam* Parser::Parse(vector<string> tokens) {
  IParam* cmdParam;

  if (false == IsValidCommandStructure(tokens)) {
    std::cerr << "INVALID COMMAND" << std::endl;
    return GetInvalidCommand();
  }

  cmdParam = GenCommandParam(tokens);

  return cmdParam;
}

bool Parser::IsValidCommandStructure(const vector<string>& tokens) {
  if (tokens.empty()) return false;

  auto it = commandParamSpecs.find(tokens[0]);
  if (it == commandParamSpecs.end()) return false;

  const CommandParamSpec& spec = it->second;

  if (tokens.size() != spec.argCount) return false;
  return spec.validator(tokens);
}

bool Parser::IsNumber(const string& str) {
  if (str.empty()) return false;
  if (str[0] == '0' && str.size() > 1 && str[1] == 'x') {
    return IsHex(str);  // Check for hexadecimal
  } else {
    return IsDec(str);  // Check for decimal number
  }
}
bool Parser::IsDec(const string& str) {
  for (char c : str) {
    if (!isdigit(c)) {
      return false;
    }
  }
  return true;
}
bool Parser::IsHex(const string& str) {
  if (str.size() < 3 || str.substr(0, 2) != "0x") {
    return false;  // Hexadecimal must start with "0x"
  }
  for (size_t i = 2; i < str.size(); ++i) {
    if (!isxdigit(str[i])) {
      return false;
    }
  }
  return true;
}