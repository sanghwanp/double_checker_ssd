#include "Parser.h"

#include <iostream>

IParam* Parser::GetCommand(int argc, char* argv[]) {
  std::vector<std::string> tokens = Parse(argc, argv);

  if (!CheckParamValid(tokens)) {
    return GenInvalidCommand();
  }

  return GenCommandParam(tokens);
}

std::vector<std::string>& Parser::Parse(int argc, char* argv[]) {
  std::vector<std::string> args;

  for (int i = 1; i < argc; i++) {
    args.emplace_back(argv[i]);
  }

  return args;
}

bool Parser::CheckParamValid(const vector<string>& tokens) {
  if (tokens.empty()) return false;
  auto it = commandParamSpecs.find(tokens[0]);
  if (it == commandParamSpecs.end()) return false;
  return tokens.size() == it->second.argCount && it->second.validator(tokens);
}

IParam* Parser::GenCommandParam(const vector<string>& tokens) {
  auto it = commandParamSpecs.find(tokens[0]);
  if (it == commandParamSpecs.end()) return GenInvalidCommand();
  return it->second.paramObj(tokens);
}
