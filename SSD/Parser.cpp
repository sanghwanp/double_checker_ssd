#include "Parser.h"

#include <iostream>
using namespace std;


IParam* Parser::GetParam(int argc, char* argv[]) {
  cout << "parser Getparam \n";
  std::vector<std::string> tokens = Parse(argc, argv);
  cout << "parser Getparam    " << tokens.empty() <<  endl;
  if (!CheckParamValid(tokens)) {
    cout << "Generate Invalid\n";
    return GenInvalidCommand();
  }
  cout << "Generate valid\n";
  //return GenCommandParam(tokens);
}


std::vector<std::string>& Parser::Parse(int argc, char* argv[]) {
  std::vector<std::string> args{};
  cout << "parser Parse \n";
  cout << argc << endl;
  cout << argv[0] << endl;
  
  for (int i = 1; i < argc; i++) {
    args.emplace_back(argv[i]);
    cout << argv[i]<< endl;
  }
  cout << args.size() <<  args.empty() << endl;
  return args;
}


bool Parser::CheckParamValid(const vector<string>& tokens) {
  cout << "***********"  << tokens.empty() << ' ' << tokens.size() << endl;
  if (tokens.empty()) return false;
  cout << "Check Param Valid    " << &tokens << " " << tokens[0] << endl;
  auto it = commandParamSpecs.find(tokens[0]);
  if (it == commandParamSpecs.end()) return false;
  return tokens.size() == it->second.argCount && it->second.validator(tokens);
}

IParam* Parser::GenCommandParam(const vector<string>& tokens) {
  auto it = commandParamSpecs.find(tokens[0]);
  if (it == commandParamSpecs.end()) return GenInvalidCommand();
  return it->second.paramObj(tokens);
}
