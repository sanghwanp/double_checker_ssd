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

    WritePresetValueAll();
  }

  void TearDown() override { std::cout.rdbuf(oldCoutStreamBuf); }

  std::string GetCoutStr() { return oss.str(); }

  bool CheckSuccess() { return GetCoutStr() == "[Eraserange] Done\n"; }

  void ClearCoutStr() { oss.str(""); }

  std::string GetPresetValue(unsigned int lba) {
    std::stringstream ss;
    // we print lba + 1, to avoid setting 0x00000000 for lba = 0
    ss << "0x" << std::setw(8) << std::setfill('0') << std::hex << (lba + 1);
    return ss.str();
  }

  void WritePresetValue(unsigned int lba) {
    auto value = GetPresetValue(lba);
    ssd.Write(lba, value);
  }

  void WritePresetValueAll() {
    for (unsigned int lba = 0; lba < 100; lba++) {
      WritePresetValue(lba);
    }
  }

  void CheckPreset(unsigned int lba) {
    EXPECT_EQ(ssd.Read(lba), GetPresetValue(lba));
  }

  void CheckErased(unsigned int lba) {
    EXPECT_EQ(ssd.Read(lba), DEFAULT_VALUE);
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

  for (unsigned int lba = 0; lba < 100; lba++) {
    CheckPreset(lba);
  }
}

TEST_F(EraseRangeTestFixture, SingleCmd) {
  EXPECT_TRUE(cmd.Call({"erase_range", "50", "54"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 50; lba++) {
    CheckPreset(lba);
  }
  for (unsigned int lba = 50; lba < 55; lba++) {
    CheckErased(lba);
  }
  for (unsigned int lba = 55; lba < 100; lba++) {
    CheckPreset(lba);
  }
}

TEST_F(EraseRangeTestFixture, SingleCmdBackwards) {
  EXPECT_TRUE(cmd.Call({"erase_range", "54", "50"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 50; lba++) {
    CheckPreset(lba);
  }
  for (unsigned int lba = 50; lba < 55; lba++) {
    CheckErased(lba);
  }
  for (unsigned int lba = 55; lba < 100; lba++) {
    CheckPreset(lba);
  }
}

TEST_F(EraseRangeTestFixture, MultiCmd) {
  EXPECT_TRUE(cmd.Call({"erase_range", "45", "70"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 45; lba++) {
    CheckPreset(lba);
  }
  for (unsigned int lba = 45; lba < 71; lba++) {
    CheckErased(lba);
  }
  for (unsigned int lba = 71; lba < 100; lba++) {
    CheckPreset(lba);
  }
}

TEST_F(EraseRangeTestFixture, MultiCmdBackwards) {
  EXPECT_TRUE(cmd.Call({"erase_range", "70", "45"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 45; lba++) {
    CheckPreset(lba);
  }
  for (unsigned int lba = 45; lba < 71; lba++) {
    CheckErased(lba);
  }
  for (unsigned int lba = 71; lba < 100; lba++) {
    CheckPreset(lba);
  }
}

TEST_F(EraseRangeTestFixture, FullErase) {
  EXPECT_TRUE(cmd.Call({"erase_range", "0", "99"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 100; lba++) {
    CheckErased(lba);
  }
}

TEST_F(EraseRangeTestFixture, FullEraseBackwards) {
  EXPECT_TRUE(cmd.Call({"erase_range", "99", "0"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 100; lba++) {
    CheckErased(lba);
  }
}

TEST_F(EraseRangeTestFixture, EdgeCase) {
  EXPECT_TRUE(cmd.Call({"erase_range", "70", "99"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 70; lba++) {
    CheckPreset(lba);
  }
  for (unsigned int lba = 70; lba < 100; lba++) {
    CheckErased(lba);
  }
}

TEST_F(EraseRangeTestFixture, EdgeCaseBackwards) {
  EXPECT_TRUE(cmd.Call({"erase_range", "99", "70"}));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 70; lba++) {
    CheckPreset(lba);
  }
  for (unsigned int lba = 70; lba < 100; lba++) {
    CheckErased(lba);
  }
}
