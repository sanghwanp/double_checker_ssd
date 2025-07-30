#include <iostream>
#include <cctype>

#include "Parser.h"

// ���ڿ��� ���� �������� �и�
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
  auto it = commandSpecs.find(tokens[0]);
  return it->second.paramObj(tokens);
}

IParam* Parser::Parse(const std::string& input) {
  vector<std::string> tokens;
  IParam* cmdParam;

  if (input == "") {
    return GetInvalidCommand();
  }

  tokens = SplitArgs(input);

  if (false == IsValidCommandStructure(tokens)) {
    std::cerr << "Error: Invalid command structure." << std::endl;
    return GetInvalidCommand();
  }

  cmdParam = GenCommandParam(tokens);

  return cmdParam;
}

bool Parser::IsValidCommandStructure(const vector<std::string>& tokens) {
    if (tokens.empty()) return false;

    auto it = commandSpecs.find(tokens[0]);
    if (it == commandSpecs.end()) return false;

    const CommandSpec& spec = it->second;

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