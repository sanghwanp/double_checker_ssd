#include <iostream>
#include <sstream>
#include <string>

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

  std::string GetPresetValue(unsigned int lba) {
    std::stringstream ss;
    ss << "0x" << std::setw(8) << std::setfill('0') << std::hex << lba;
    return ss.str();
  }

  void WritePresetValue(unsigned int lba) {
    auto value = GetPresetValue(lba);
    ssd.Write(lba, value);
  }

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
  for (unsigned int lba = 0; lba < 5; lba++) {
    WritePresetValue(lba);
  }

  EXPECT_TRUE(cmd.Call({"erase", "0", "5"}));
  CheckSuccess();

  for (unsigned int lba = 0; lba < 5; lba++) {
    EXPECT_EQ(DEFAULT_VALUE, ssd.Read(lba));
  }
}

TEST_F(EraseTestFixture, EraseSingleCmdBackwards) {
  for (unsigned int lba = 0; lba < 5; lba++) {
    WritePresetValue(lba);
  }

  EXPECT_TRUE(cmd.Call({"erase", "4", "-5"}));
  CheckSuccess();

  for (unsigned int lba = 0; lba < 5; lba++) {
    EXPECT_EQ(DEFAULT_VALUE, ssd.Read(lba));
  }
}

TEST_F(EraseTestFixture, EraseMultiCmd) {
  for (unsigned int lba = 0; lba < 15; lba++) {
    WritePresetValue(lba);
  }

  EXPECT_TRUE(cmd.Call({"erase", "0", "11"}));
  CheckSuccess();

  for (unsigned int lba = 0; lba < 11; lba++) {
    EXPECT_EQ(DEFAULT_VALUE, ssd.Read(lba));
  }
  for (unsigned int lba = 11; lba < 15; lba++) {
    EXPECT_EQ(GetPresetValue(lba), ssd.Read(lba));
  }
}

TEST_F(EraseTestFixture, EraseFull) {
  for (unsigned int lba = 0; lba < 100; lba++) {
    WritePresetValue(lba);
  }

  cmd.Call({"erase", "0", "100"});

  for (unsigned int lba = 0; lba < 100; lba++) {
    EXPECT_EQ(DEFAULT_VALUE, ssd.Read(lba));
  }
}

TEST_F(EraseTestFixture, EraseFullBackwards) {
  for (unsigned int lba = 0; lba < 100; lba++) {
    WritePresetValue(lba);
  }

  cmd.Call({"erase", "99", "-100"});

  for (unsigned int lba = 0; lba < 100; lba++) {
    EXPECT_EQ(DEFAULT_VALUE, ssd.Read(lba));
  }
}

TEST_F(EraseTestFixture, EraseFullOverRange) {
  for (unsigned int lba = 0; lba < 100; lba++) {
    WritePresetValue(lba);
  }

  cmd.Call({"erase", "0", "300"});

  for (unsigned int lba = 0; lba < 100; lba++) {
    EXPECT_EQ(DEFAULT_VALUE, ssd.Read(lba));
  }
}
