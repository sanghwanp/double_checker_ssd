#include <iostream>
#include <sstream>

#include "../Shell/CmdRead.h"
#include "../Shell/MockSSD.h"
#include "gmock/gmock.h"

using namespace testing;

class ReadTestFixture : public Test {
 public:
  void SetUp() override {
    oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
  }

  void TearDown() override { std::cout.rdbuf(oldCoutStreamBuf); }

  std::string GetCoutStr() { return oss.str(); }

  std::ostringstream oss;
  std::streambuf* oldCoutStreamBuf;

  MockSSD ssd;
  CommandRead cmd{&ssd};
};

TEST_F(ReadTestFixture, ReadDefault) {
  EXPECT_TRUE(cmd.Call({"read", "1"}));

  std::string outputStr = GetCoutStr();
  EXPECT_EQ("[Read] LBA 1 : 0x00000000\n", outputStr);
}

TEST_F(ReadTestFixture, ReadValue) {
  ssd.Write(1, "0x12345678");

  EXPECT_TRUE(cmd.Call({"read", "1"}));

  std::string outputStr = GetCoutStr();
  EXPECT_EQ("[Read] LBA 1 : 0x12345678\n", outputStr);
}

TEST_F(ReadTestFixture, ReadInvalidLBA) {
  EXPECT_FALSE(cmd.Call({"read", "100"}));
  EXPECT_FALSE(cmd.Call({"read", "200"}));
}
