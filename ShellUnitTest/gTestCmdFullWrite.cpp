#include "../Shell/CmdFullWrite.h"
#include "../Shell/MockSSD.h"  // �̸��� FakeSSD�� �ٲٴ� �� ��õ!
#include "gtest/gtest.h"

class FullWriteTest : public ::testing::Test {
 protected:
  MockSSD ssd;  // ������ FakeSSD
  CommandFullWrite* cmd;

  void SetUp() override { cmd = new CommandFullWrite(&ssd); }

  void TearDown() override { delete cmd; }
};

TEST_F(FullWriteTest, FullWriteSuccess) {
  std::vector<std::string> program = {"fullwrite", "0xABCDEF12"};
  EXPECT_TRUE(cmd->Call(program));

  for (int i = 0; i < 100; ++i) {
    EXPECT_EQ("0xABCDEF12", ssd.Read(i));
  }
}

TEST_F(FullWriteTest, InvalidCommand_MissingArgs) {
  std::vector<std::string> program = {"fullwrite"};
  EXPECT_FALSE(cmd->Call(program));
}

TEST_F(FullWriteTest, InvalidCommand_TooManyArgs) {
  std::vector<std::string> program = {"fullwrite", "0xABCDEF12", "extra"};
  EXPECT_FALSE(cmd->Call(program));
}

TEST_F(FullWriteTest, InvalidCommand_ValueTooShort) {
  std::vector<std::string> program = {"fullwrite", "0xABC"};
  EXPECT_FALSE(cmd->Call(program));
}

TEST_F(FullWriteTest, InvalidCommand_ValueNotPrefixed) {
  std::vector<std::string> program = {"fullwrite", "ABCDEF1234"};
  EXPECT_FALSE(cmd->Call(program));
}

TEST_F(FullWriteTest, InvalidCommand_ValueContainsInvalidChar) {
  std::vector<std::string> program = {"fullwrite", "0xABCDZZ12"};
  EXPECT_FALSE(cmd->Call(program));
}

TEST_F(FullWriteTest, InvalidCommand_ValueTooLong) {
  std::vector<std::string> program = {"fullwrite", "0x1234567890"};
  EXPECT_FALSE(cmd->Call(program));
}
