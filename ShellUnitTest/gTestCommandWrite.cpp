#include "../Shell/CmdWrite.h"
#include "../Shell/MockSSD.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace testing;

const std::string INVALID_COMMAND_MESSAGE = "INVALID COMMAND\n";
const std::string SUCCESS_MESSSAGE = "[Write] Done\n";

TEST(CommandWriteTest, WriteValid) {
  std::ostringstream oss;
  auto oldCout = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  MockSSD ssd;
  CommandWrite cmd(&ssd);

  EXPECT_EQ(true, cmd.Call({"write", "3", "0xABCDEF01"}));

  std::cout.rdbuf(oldCout);
  std::string output = oss.str();

  EXPECT_EQ(SUCCESS_MESSSAGE, output);
}

TEST(CommandWriteTest, WriteInvalidLBA) {
  std::ostringstream oss;
  auto oldCout = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  MockSSD ssd;
  CommandWrite cmd(&ssd);

  EXPECT_EQ(false, cmd.Call({"write", "-1", "0x12345678"}));

  std::cout.rdbuf(oldCout);
  std::string output = oss.str();

  EXPECT_EQ(INVALID_COMMAND_MESSAGE, output);
}

TEST(CommandWriteTest, WriteInvalidValue) {
  std::ostringstream oss;
  auto oldCout = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  MockSSD ssd;
  CommandWrite cmd(&ssd);

  EXPECT_EQ(false, cmd.Call({"write", "3", "1234GHIJ"}));

  std::cout.rdbuf(oldCout);
  std::string output = oss.str();

  EXPECT_EQ(INVALID_COMMAND_MESSAGE, output);
}

TEST(CommandWriteTest, WriteMissingArgs) {
  std::ostringstream oss;
  auto oldCout = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  MockSSD ssd;
  CommandWrite cmd(&ssd);

  EXPECT_EQ(false, cmd.Call({"write", "3"}));

  std::cout.rdbuf(oldCout);
  std::string output = oss.str();

  EXPECT_EQ(INVALID_COMMAND_MESSAGE, output);
}
