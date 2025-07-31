#include <iostream>
#include <sstream>

#include "../Shell/CmdErase.h"
#include "../Shell/MockSSD.h"
#include "gmock/gmock.h"

using namespace testing;

class EraseTestFixture : public Test {
 public:
  void SetUp() override {
    oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
  }

  void TearDown() override { std::cout.rdbuf(oldCoutStreamBuf); }

  std::string GetCoutStr() { return oss.str(); }

  bool CheckSuccess() { return GetCoutStr() == "[Erase] Done\n"; }

  bool ClearCoutStr() { oss.clear(); }

  std::ostringstream oss;
  std::streambuf* oldCoutStreamBuf;

  MockSSD ssd;
  CommandErase cmd{&ssd};
  const char* DEFAULT_VALUE = "0x00000000";
};

TEST_F(EraseTestFixture, EraseInvalidLBA) {
  EXPECT_FALSE(cmd.Call({"erase", "-1", "20"}));
  CheckSuccess();
}

TEST_F(EraseTestFixture, EraseZero) {
  EXPECT_TRUE(cmd.Call({"erase", "0", "0"}));
  CheckSuccess();
  EXPECT_TRUE(cmd.Call({"erase", "50", "0"}));
  CheckSuccess();
  EXPECT_TRUE(cmd.Call({"erase", "99", "0"}));
  CheckSuccess();
}

TEST_F(EraseTestFixture, EraseSingleCmd) {
  ssd.Write(0, "0x10000000");
  ssd.Write(1, "0x11000000");
  ssd.Write(2, "0x12000000");
  ssd.Write(3, "0x13000000");
  ssd.Write(4, "0x14000000");

  EXPECT_TRUE(cmd.Call({"erase", "0", "5"}));
  CheckSuccess();

  EXPECT_EQ(ssd.Read(0), DEFAULT_VALUE);
  EXPECT_EQ(ssd.Read(1), DEFAULT_VALUE);
  EXPECT_EQ(ssd.Read(2), DEFAULT_VALUE);
  EXPECT_EQ(ssd.Read(3), DEFAULT_VALUE);
  EXPECT_EQ(ssd.Read(4), DEFAULT_VALUE);
}

TEST_F(EraseTestFixture, EraseSingleCmdBackwards) {
  ssd.Write(0, "0x10000000");
  ssd.Write(1, "0x11000000");
  ssd.Write(2, "0x12000000");
  ssd.Write(3, "0x13000000");
  ssd.Write(4, "0x14000000");

  EXPECT_TRUE(cmd.Call({"erase", "4", "-5"}));
  CheckSuccess();

  EXPECT_EQ(ssd.Read(0), DEFAULT_VALUE);
  EXPECT_EQ(ssd.Read(1), DEFAULT_VALUE);
  EXPECT_EQ(ssd.Read(2), DEFAULT_VALUE);
  EXPECT_EQ(ssd.Read(3), DEFAULT_VALUE);
  EXPECT_EQ(ssd.Read(4), DEFAULT_VALUE);
}

TEST_F(EraseTestFixture, EraseMultiCmd) {
  ssd.Write(0, "0x10000000");
  ssd.Write(1, "0x11000000");
  ssd.Write(2, "0x12000000");
  ssd.Write(3, "0x13000000");
  ssd.Write(4, "0x14000000");
  ssd.Write(5, "0x15000000");
  ssd.Write(6, "0x16000000");
  ssd.Write(7, "0x17000000");
  ssd.Write(8, "0x18000000");
  ssd.Write(9, "0x19000000");
  ssd.Write(10, "0x20000000");
  ssd.Write(11, "0x21000000");
  ssd.Write(12, "0x22000000");
  ssd.Write(13, "0x23000000");
  ssd.Write(14, "0x24000000");

  EXPECT_TRUE(cmd.Call({"erase", "0", "11"}));
  CheckSuccess();

  for (int i = 0; i < 11; i++) {
    EXPECT_EQ(ssd.Read(i), DEFAULT_VALUE);
  }

  EXPECT_EQ(ssd.Read(11), "0x21000000");
  EXPECT_EQ(ssd.Read(12), "0x22000000");
  EXPECT_EQ(ssd.Read(13), "0x23000000");
  EXPECT_EQ(ssd.Read(14), "0x24000000");
}
