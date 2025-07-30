#include "Parser.h"
#include <iostream>

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

CommandStruct Parser::Parse(const std::string& input) {
  vector<std::string> tokens;
  CommandStruct cmd;
  int pos = 0;
  int found;
  string token;
  string inputCopy = input;

  if (input == "") {
    cmd.commandName = "error";
    return cmd;
  }

  tokens = SplitArgs(input);

  if (false == CheckTokensStruct(tokens, inputCopy.substr(pos))) {
    std::cerr << "Error: Invalid command structure." << std::endl;
    cmd.commandName = "error";
    return cmd;
  }

  cmd.commandName = tokens[0];
  if (tokens.size() > 1) {
    cmd.firstNumber = tokens[1];
  }
  if (tokens.size() > 2) {
    cmd.secondNumber = tokens[2];
  }

  return cmd;
}
bool Parser::CheckTokensStruct(const vector<std::string>& tokens,
                               const string& lastToken) {
  if (tokens.empty()) {
    return false;  // No command provided
  }

  if (tokens[0] != "write" && tokens[0] != "read" && tokens[0] != "exit" &&
      tokens[0] != "help" && tokens[0] != "fullwrite" &&
      tokens[0] != "fullread") {
    return false;  // Invalid command
  }

  if (tokens[0] == "write") {
    if (tokens.size() != 3 || !IsNumberOrHex(tokens[1]) ||
        !IsNumberOrHex(tokens[2])) {
      return false;  // Invalid write command structure
    }
  } else if (tokens[0] == "read" || tokens[0] == "fullwrite") {
    if (tokens.size() != 2 || !IsNumberOrHex(tokens[1])) {
      return false;  // Invalid read command structure
    }
  } else if (tokens[0] == "exit" || tokens[0] == "help" ||
             tokens[0] == "fullread") {
    if (tokens.size() != 1) {
      return false;  // Invalid exit or help command structure
    }
  }
}

bool Parser::IsNumberOrHex(const std::string& str) {
  if (str.empty()) return false;
  if (str[0] == '0' && str.size() > 1 && str[1] == 'x') {
    return IsHex(str);  // Check for hexadecimal
  } else {
    return IsNumber(str);  // Check for decimal number
  }
}
bool Parser::IsNumber(const std::string& str) {
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