#include <iostream>

#include "Parser.h"

IParam* Parser::Parse(const vector<string>& tokens) {
  if (!IsValidCommandStructure(tokens)) {
    return GetInvalidCommand();
  }
  return GenCommandParam(tokens);
}

bool Parser::IsValidCommandStructure(const vector<string>& tokens) {
  if (tokens.empty()) return false;
  auto it = commandParamSpecs.find(tokens[0]);
  if (it == commandParamSpecs.end()) return false;
  return tokens.size() == it->second.argCount && it->second.validator(tokens);
}

IParam* Parser::GenCommandParam(const vector<string>& tokens) {
  auto it = commandParamSpecs.find(tokens[0]);
  if (it == commandParamSpecs.end()) return GetInvalidCommand();
  return it->second.paramObj(tokens);
}
