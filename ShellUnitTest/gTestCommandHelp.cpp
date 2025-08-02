#include "../Shell/CmdHelp.h"
#include "../Shell/Parser.h"
#include "gtest/gtest.h"
#include <iostream>
#include <sstream>
#include <string>
#include "gTestCommandCallCommon.h"

using namespace testing;

class CommandHelpTest : public CommandCallCommon {
 protected:
  std::ostringstream oss;
  std::streambuf* originalCout;

  void SetUp() override {
    originalCout = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
  }

  void TearDown() override { std::cout.rdbuf(originalCout); }

  std::string GetOutput() { return oss.str(); }
};

TEST_F(CommandHelpTest, HelpOutputContainsTeamInfoAndAllCommands) {
  CommandHelp helpCommand;

  bool result = helpCommand.Call(GenParam({""}));

  EXPECT_TRUE(result);

  std::string output = GetOutput();

  EXPECT_NE(output.find("Team Info"), std::string::npos);
  EXPECT_NE(output.find("write"), std::string::npos);
  EXPECT_NE(output.find("read"), std::string::npos);
  EXPECT_NE(output.find("fullwrite"), std::string::npos);
  EXPECT_NE(output.find("fullread"), std::string::npos);
  EXPECT_NE(output.find("help"), std::string::npos);
  EXPECT_NE(output.find("exit"), std::string::npos);

  EXPECT_NE(output.find("erase"), std::string::npos);
  EXPECT_NE(output.find("erase_range"), std::string::npos);
  EXPECT_NE(output.find("flush"), std::string::npos);
  EXPECT_NE(output.find("test script 1"), std::string::npos);
  EXPECT_NE(output.find("test script 2"), std::string::npos);
  EXPECT_NE(output.find("test script 3"), std::string::npos);
  EXPECT_NE(output.find("test script 4"), std::string::npos);
}
