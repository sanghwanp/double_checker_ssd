#include "../Shell/CmdFullWrite.h"
#include "../Shell/MockSSD.h"  // 이름은 FakeSSD로 바꾸는 걸 추천!
#include "../Shell/Parser.h"
#include "gTestCommandCallCommon.h"
#include "gtest/gtest.h"

class FullWriteTest : public CommandCallCommon {
protected:
  MockSSD ssd;  // 실제는 FakeSSD
  CommandFullWrite* cmd;

  void SetUp() override { cmd = new CommandFullWrite(&ssd); }

  void TearDown() override { delete cmd; }
};

TEST_F(FullWriteTest, FullWriteSuccess) {
  std::string program = "fullwrite 0xABCDEF12";
  EXPECT_TRUE(cmd->Call(GenParam(program)));

  for (unsigned i = 0; i < 100; ++i) {
    EXPECT_EQ("0xABCDEF12", ssd.Read(i));
  }
}

TEST_F(FullWriteTest, InvalidCommand_MissingArgs) {
  std::string program = "fullwrite";
  EXPECT_FALSE(cmd->Call(GenParam(program)));
}

TEST_F(FullWriteTest, InvalidCommand_TooManyArgs) {
  std::string program = "fullwrite 0xABCDEF12 extra";
  EXPECT_FALSE(cmd->Call(GenParam(program)));
}

TEST_F(FullWriteTest, InvalidCommand_ValueTooShort) {
  std::string program = "fullwrite 0xABC";
  EXPECT_FALSE(cmd->Call(GenParam(program)));
}

TEST_F(FullWriteTest, InvalidCommand_ValueNotPrefixed) {
  std::string program = "fullwrite ABCDEF1234";
  EXPECT_FALSE(cmd->Call(GenParam(program)));
}

TEST_F(FullWriteTest, InvalidCommand_ValueContainsInvalidChar) {
  std::string program = "fullwrite 0xABCDZZ12";
  EXPECT_FALSE(cmd->Call(GenParam(program)));
}

TEST_F(FullWriteTest, InvalidCommand_ValueTooLong) {
  std::string program = "fullwrite 0x1234567890";
  EXPECT_FALSE(cmd->Call(GenParam(program)));
}
