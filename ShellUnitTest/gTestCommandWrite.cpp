#include <iostream>

#include "../Shell/CmdWrite.h"
#include "../Shell/MockSSD.h"
#include "gtest/gtest.h"

using namespace testing;

const std::string INVALID_COMMAND_MESSAGE = "INVALID COMMAND\n";
const std::string SUCCESS_MESSAGE = "[Write] Done\n";

class CommandWriteTest : public Test {
 protected:
  std::ostringstream oss;
  std::streambuf* oldCout;
  MockSSD ssd;
  CommandWrite* cmd;

  void SetUp() override {
    oldCout = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    cmd = new CommandWrite(&ssd);
  }

  void TearDown() override {
    std::cout.rdbuf(oldCout);
    delete cmd;
  }

  std::string GetOutput() { return oss.str(); }
};

TEST_F(CommandWriteTest, WriteValid) {
  EXPECT_TRUE(cmd->Call({"write", "3", "0xABCDEF01"}));
  EXPECT_EQ(SUCCESS_MESSAGE, GetOutput());
}

TEST_F(CommandWriteTest, WriteInvalidLBA) {
  EXPECT_FALSE(cmd->Call({"write", "-1", "0x12345678"}));
  EXPECT_EQ(INVALID_COMMAND_MESSAGE, GetOutput());
}

TEST_F(CommandWriteTest, WriteInvalidValue) {
  EXPECT_FALSE(cmd->Call({"write", "3", "1234GHIJ"}));
  EXPECT_EQ(INVALID_COMMAND_MESSAGE, GetOutput());
}

TEST_F(CommandWriteTest, WriteMissingArgs) {
  EXPECT_FALSE(cmd->Call({"write", "3"}));
  EXPECT_EQ(INVALID_COMMAND_MESSAGE, GetOutput());
}