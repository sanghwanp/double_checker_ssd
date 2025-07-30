#include "../Shell/CmdWrite.h"
#include "../Shell/MockSSD.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace testing;

TEST(CommandWriteTest, WriteValid) {
  std::ostringstream oss;
  auto oldCout = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  MockSSD ssd;
  CommandWrite cmd(&ssd);

  EXPECT_EQ(true, cmd.Call({"write", "3", "0xABCDEF01"}));

  std::cout.rdbuf(oldCout);
  std::string output = oss.str();

  EXPECT_EQ("[Write] Done\n", output);
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

  EXPECT_EQ("ERROR\n", output);
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

  EXPECT_EQ("ERROR\n", output);
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

  EXPECT_EQ("ERROR\n", output);
}
