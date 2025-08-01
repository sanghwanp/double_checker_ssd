#pragma once
#include "gtest/gtest.h"
#include "../Shell/Parser.h"
#include "../Shell/ICommand.h"

class CommandCallCommon : public ::testing::Test {
 public:
  IParam& GenParam(const std::string& args) {

    return *parser.Parse(args);
  }
  bool CallCommand(const std::string& args) {
    param = &GenParam(args);
    cmdHandler = ICommandFactory::GetInstance()->CreateCommand(*param);
    if (cmdHandler == nullptr) {
      std::cout << INVALID_MESSAGE;
      return false;
    }

    cmdHandler->Call(*param);
    delete cmdHandler;
    delete param;
    return true;
  }
  const std::string INVALID_MESSAGE = "INVALID COMMAND\n";
  Parser parser;
  IShellCommand* cmdHandler;
  IParam* param;
};

