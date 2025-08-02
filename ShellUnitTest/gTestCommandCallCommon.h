#pragma once
#include "gtest/gtest.h"
#include "../Shell/Parser.h"
#include "../Shell/ICommand.h"
#include "../Shell/MockSSD.h"
#include "../Shell/RealSSD.h"
#include "../Shell/ICommandFactory.h"
#include "../Shell/CmdTestScript.h"

class CommandCallCommon : public ::testing::Test {
 public:
  IParam& GenParam(const std::string& args) {

    return *parser.Parse(args);
  }
  bool CallCommand(const std::string& args) {
    bool ret = false;
    param = &GenParam(args);
    cmdHandler = ICommandFactory::GetInstance()->CreateCommand(*param, &mockSsd);
    if (cmdHandler != nullptr)
    {
      ret = cmdHandler->Call(*param);
    } else if (param->eCmd == eScriptCmd) {
      IScriptCommand* scriptCmd = new CommandTestScript{&mockSsd};
      if (scriptCmd != nullptr) {
        std::string result = scriptCmd->Call(*param);
        std::cout << result << std::endl;
      }
    }else {
      std::cout << INVALID_MESSAGE;
    }

    delete cmdHandler;
    delete param;
    return ret;
  }
  const std::string INVALID_MESSAGE = "INVALID COMMAND\n";
  Parser parser;
  IShellCommand* cmdHandler;
  IParam* param;
  MockSSD mockSsd;
};

