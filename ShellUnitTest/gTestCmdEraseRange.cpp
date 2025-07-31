#include <iostream>
#include <sstream>
#include <string>

#include "../Shell/CmdEraseRange.h"
#include "../Shell/MockSSD.h"
#include "gmock/gmock.h"

using namespace testing;

class EraseRangeTestFixture : public Test {
 public:
  void SetUp() override {
    oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
  }

  void TearDown() override { std::cout.rdbuf(oldCoutStreamBuf); }

  std::string GetCoutStr() { return oss.str(); }

  bool CheckSuccess() { return GetCoutStr() == "[Eraserange] Done\n"; }

  void ClearCoutStr() { oss.str(""); }

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
  CommandEraseRange cmd{&ssd};
  const char* DEFAULT_VALUE = "0x00000000";
};

TEST_F(EraseRangeTestFixture, InvalidLBA) {
  EXPECT_FALSE(cmd.Call({"erase_range", "-1", "0"}));
  EXPECT_FALSE(cmd.Call({"erase_range", "0", "-1"}));
  EXPECT_FALSE(cmd.Call({"erase_range", "-1", "100"}));
  EXPECT_FALSE(cmd.Call({"erase_range", "100", "-1"}));
  EXPECT_FALSE(cmd.Call({"erase_range", "99", "100"}));
  EXPECT_FALSE(cmd.Call({"erase_range", "100", "99"}));
}

TEST_F(EraseRangeTestFixture, SingleCmd) {
  for (unsigned int lba = 0; lba < 100; lba++) {
    WritePresetValue(lba);
  }

  EXPECT_TRUE(cmd.Call({"erase_range", "50", "54"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 50; lba++) {
    EXPECT_EQ(GetPresetValue(lba), ssd.Read(lba));
  }
  for (unsigned int lba = 50; lba < 55; lba++) {
    EXPECT_EQ(DEFAULT_VALUE, ssd.Read(lba));
  }
  for (unsigned int lba = 55; lba < 100; lba++) {
    EXPECT_EQ(GetPresetValue(lba), ssd.Read(lba));
  }
}

TEST_F(EraseRangeTestFixture, SingleCmdBackwards) {
  for (unsigned int lba = 0; lba < 100; lba++) {
    WritePresetValue(lba);
  }

  EXPECT_TRUE(cmd.Call({"erase_range", "54", "50"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 50; lba++) {
    EXPECT_EQ(GetPresetValue(lba), ssd.Read(lba));
  }
  for (unsigned int lba = 50; lba < 55; lba++) {
    EXPECT_EQ(DEFAULT_VALUE, ssd.Read(lba));
  }
  for (unsigned int lba = 55; lba < 100; lba++) {
    EXPECT_EQ(GetPresetValue(lba), ssd.Read(lba));
  }
}

TEST_F(EraseRangeTestFixture, MultiCmd) {
  for (unsigned int lba = 0; lba < 100; lba++) {
    WritePresetValue(lba);
  }

  EXPECT_TRUE(cmd.Call({"erase_range", "45", "70"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 45; lba++) {
    EXPECT_EQ(GetPresetValue(lba), ssd.Read(lba));
  }
  for (unsigned int lba = 45; lba < 71; lba++) {
    EXPECT_EQ(DEFAULT_VALUE, ssd.Read(lba));
  }
  for (unsigned int lba = 71; lba < 100; lba++) {
    EXPECT_EQ(GetPresetValue(lba), ssd.Read(lba));
  }
}

TEST_F(EraseRangeTestFixture, MultiCmdBackwards) {
  for (unsigned int lba = 0; lba < 100; lba++) {
    WritePresetValue(lba);
  }

  EXPECT_TRUE(cmd.Call({"erase_range", "70", "45"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 45; lba++) {
    EXPECT_EQ(GetPresetValue(lba), ssd.Read(lba));
  }
  for (unsigned int lba = 45; lba < 71; lba++) {
    EXPECT_EQ(DEFAULT_VALUE, ssd.Read(lba));
  }
  for (unsigned int lba = 71; lba < 100; lba++) {
    EXPECT_EQ(GetPresetValue(lba), ssd.Read(lba));
  }
}

TEST_F(EraseRangeTestFixture, FullErase) {
  for (unsigned int lba = 0; lba < 100; lba++) {
    WritePresetValue(lba);
  }

  EXPECT_TRUE(cmd.Call({"erase_range", "0", "99"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 100; lba++) {
    EXPECT_EQ(DEFAULT_VALUE, ssd.Read(lba));
  }
}

TEST_F(EraseRangeTestFixture, FullEraseBackwards) {
  for (unsigned int lba = 0; lba < 100; lba++) {
    WritePresetValue(lba);
  }

  EXPECT_TRUE(cmd.Call({"erase_range", "99", "0"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 100; lba++) {
    EXPECT_EQ(DEFAULT_VALUE, ssd.Read(lba));
  }
}

TEST_F(EraseRangeTestFixture, EdgeCase) {
  for (unsigned int lba = 0; lba < 100; lba++) {
    WritePresetValue(lba);
  }

  EXPECT_TRUE(cmd.Call({"erase_range", "70", "99"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 70; lba++) {
    EXPECT_EQ(GetPresetValue(lba), ssd.Read(lba));
  }
  for (unsigned int lba = 70; lba < 100; lba++) {
    EXPECT_EQ(DEFAULT_VALUE, ssd.Read(lba));
  }
}

TEST_F(EraseRangeTestFixture, EdgeCaseBackwards) {
  for (unsigned int lba = 0; lba < 100; lba++) {
    WritePresetValue(lba);
  }

  EXPECT_TRUE(cmd.Call({"erase_range", "99", "70"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 70; lba++) {
    EXPECT_EQ(GetPresetValue(lba), ssd.Read(lba));
  }
  for (unsigned int lba = 70; lba < 100; lba++) {
    EXPECT_EQ(DEFAULT_VALUE, ssd.Read(lba));
  }
}
