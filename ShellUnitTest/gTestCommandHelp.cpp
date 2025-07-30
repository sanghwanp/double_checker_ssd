#include "../Shell/CmdHelp.h"
#include "gtest/gtest.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace testing;

class CommandHelpTest : public Test {
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
  bool result = helpCommand.Call({});

  EXPECT_TRUE(result);

  std::string output = GetOutput();

  EXPECT_NE(output.find("Team Info"), std::string::npos);
  EXPECT_NE(output.find("write [LBA] [Value]"), std::string::npos);
  EXPECT_NE(output.find("read [LBA]"), std::string::npos);
  EXPECT_NE(output.find("fullwrite [Value]"), std::string::npos);
  EXPECT_NE(output.find("fullread"), std::string::npos);
  EXPECT_NE(output.find("help"), std::string::npos);
  EXPECT_NE(output.find("exit"), std::string::npos);
}