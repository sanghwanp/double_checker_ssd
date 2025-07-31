#include <iostream>
#include <cctype>
#include <regex>
#include "Parser.h"

string Parser::ExtractScriptNumberIfValidFormat(const std::string& str) {
  static const std::regex pattern(R"(^(\d+)_.*$)");
  std::smatch match;

  if (std::regex_match(str, match, pattern)) {
    return match[1].str();  // 첫 번째 캡처 그룹(숫자) 반환
  }

  return "0";
}

std::vector<std::string> Parser::SplitArgs(const std::string& input) {
  std::vector<std::string> result;
  std::string temp;
  for (char ch : input) {
    if (std::isspace(ch)) {
      if (!temp.empty()) {
        result.push_back(temp);
        temp.clear();
      }
    } else {
      temp += ch;
    }
  }
  if (!temp.empty()) result.push_back(temp);
  return result;
}

IParam* Parser::GenCommandParam(std::vector<std::string> tokens) {
  auto it = commandParamSpecs.find(tokens[0]);
  if (it == commandParamSpecs.end()) return GetInvalidCommand();
  return it->second.paramObj(tokens);
}


IParam* Parser::Parse(const std::string& input) {
  vector<std::string> tokens;
  IParam* cmdParam;

  if (true == input.empty()) {
    return GetInvalidCommand();
  }

  tokens = SplitArgs(input);

  if (true == IsValidScriptCommandStructure(tokens)) {
    return GenScriptParam(tokens);
  }

  if (false == IsValidCommandStructure(tokens)) {
    std::cerr << "INVALID COMMAND" << std::endl;
    return GetInvalidCommand();
  }

  cmdParam = GenCommandParam(tokens);

  return cmdParam;
}

IParam * Parser::GenScriptParam(std::vector<std::string>& tokens) {
  return commandParamSpecs.at("script").paramObj(tokens);
}

bool Parser::IsValidCommandStructure(const vector<std::string>& tokens) {
    if (tokens.empty()) return false;

    auto it = commandParamSpecs.find(tokens[0]);
    if (it == commandParamSpecs.end()) return false;

    const CommandParamSpec& spec = it->second;

    if (tokens.size() != spec.argCount) return false;
    return spec.validator(tokens);
}

bool Parser::IsValidScriptCommandStructure(const vector<std::string>& tokens) {
  string scriptNumber = ExtractScriptNumberIfValidFormat(tokens[0]);

  if (scriptNumber == "0")
  {
    return false;
  }

  const CommandParamSpec& spec = commandParamSpecs.at("script");

  if (tokens.size() != spec.argCount) return false;

  return spec.validator(tokens);
}

bool Parser::IsNumber(const std::string& str) {
  if (str.empty()) return false;
  if (str[0] == '0' && str.size() > 1 && str[1] == 'x') {
    return IsHex(str);  // Check for hexadecimal
  } else {
    return IsDec(str);  // Check for decimal number
  }
}
bool Parser::IsDec(const std::string& str) {
  for (char c : str) {
    if (!isdigit(c)) {
      return false;
    }
  }
  return true;
}
bool Parser::IsHex(const std::string& str) {
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