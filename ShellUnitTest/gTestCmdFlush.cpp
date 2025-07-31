#include <iostream>
#include <sstream>

#include "../Shell/CmdFlush.h"
#include "../Shell/MockSSD.h"
#include "gtest/gtest.h"

class FlushTestFixture : public ::testing::Test {
 protected:
  void SetUp() override { oldBuf = std::cout.rdbuf(oss.rdbuf()); }
  void TearDown() override { std::cout.rdbuf(oldBuf); }

  std::string GetCout() const { return oss.str(); }

  std::ostringstream oss;
  std::streambuf* oldBuf = nullptr;

  MockSSD ssd;
  CommandFlush cmd{&ssd};
};

TEST_F(FlushTestFixture, FlushDefault) {
  // valid: exactly one token
  EXPECT_TRUE(cmd.Call({"flush"}));
  EXPECT_EQ("", GetCout());
}

TEST_F(FlushTestFixture, FlushExtraArg) {
  // invalid: too many args
  EXPECT_FALSE(cmd.Call({"flush", "now"}));
  EXPECT_EQ("INVALID COMMAND\n", GetCout());
}

TEST_F(FlushTestFixture, FlushNoArg) {
  // invalid: missing command
  EXPECT_FALSE(cmd.Call({}));
  EXPECT_EQ("INVALID COMMAND\n", GetCout());
}
