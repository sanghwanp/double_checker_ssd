#include <iostream>
#include <sstream>

#include "../Shell/CmdExit.h"
#include "gtest/gtest.h"

using namespace testing;

const std::string SHUTDOWN_MESSAGE = "Shutting down\n";
const std::string INVALID_MESSAGE = "INVALID COMMAND\n";

class CommandExitTest : public Test {
 protected:
  std::ostringstream oss;
  std::streambuf* oldCout;

  void SetUp() override {
    oldCout = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
  }

  void TearDown() override { std::cout.rdbuf(oldCout); }
};

TEST_F(CommandExitTest, ValidExitCommand) {
  CommandExit cmd;
  bool result = cmd.Call({"exit"});
  std::string output = oss.str();

  EXPECT_TRUE(result);
  EXPECT_EQ(SHUTDOWN_MESSAGE, output);
}

TEST_F(CommandExitTest, InvalidExitWithExtraArg) {
  CommandExit cmd;
  bool result = cmd.Call({"exit", "now"});
  std::string output = oss.str();

  EXPECT_FALSE(result);
  EXPECT_EQ(INVALID_MESSAGE, output);
}

TEST_F(CommandExitTest, InvalidExitWithNoArg) {
  CommandExit cmd;
  bool result = cmd.Call({});
  std::string output = oss.str();

  EXPECT_FALSE(result);
  EXPECT_EQ(INVALID_MESSAGE, output);
}
