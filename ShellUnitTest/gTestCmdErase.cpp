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
