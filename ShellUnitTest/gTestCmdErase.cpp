#include <iostream>
#include <sstream>
#include <string>

#include "../Shell/CmdErase.h"
#include "../Shell/MockSSD.h"
#include "../Shell/Parser.h"
#include "gmock/gmock.h"

using namespace testing;

class EraseTestFixture : public Test {
 public:
  void SetUp() override {
    oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    WritePresetValueAll();
  }

  void TearDown() override { std::cout.rdbuf(oldCoutStreamBuf); }

  std::string GetCoutStr() { return oss.str(); }

  bool CheckSuccess() { return GetCoutStr() == "[Erase] Done\n"; }

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

  IParam& GenEraseParam(const std::vector<std::string>& args) {
    return *parser.GenCommandParam(args);
  }
  Parser parser;

  std::ostringstream oss;
  std::streambuf* oldCoutStreamBuf;

  MockSSD ssd;
  CommandErase cmd{&ssd};
  const char* DEFAULT_VALUE = "0x00000000";
};

TEST_F(EraseTestFixture, EraseInvalidLBA) {
  EXPECT_FALSE(cmd.Call(GenEraseParam({"erase", "-1", "20"})));
  EXPECT_FALSE(CheckSuccess());

  for (unsigned int lba = 0; lba < 100; lba++) {
    CheckPreset(lba);
  }
}

TEST_F(EraseTestFixture, EraseZero) {
  EXPECT_TRUE(cmd.Call(GenEraseParam({"erase", "0", "0"})));
  EXPECT_TRUE(CheckSuccess());
  ClearCoutStr();
  EXPECT_TRUE(cmd.Call(GenEraseParam({"erase", "50", "0"})));
  EXPECT_TRUE(CheckSuccess());
  ClearCoutStr();
  EXPECT_TRUE(cmd.Call(GenEraseParam({"erase", "99", "0"})));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 100; lba++) {
    CheckPreset(lba);
  }
}

TEST_F(EraseTestFixture, EraseSingleCmd) {
  EXPECT_TRUE(cmd.Call(GenEraseParam({"erase", "0", "5"})));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 5; lba++) {
    CheckErased(lba);
  }
  for (unsigned int lba = 5; lba < 100; lba++) {
    CheckPreset(lba);
  }
}

TEST_F(EraseTestFixture, EraseSingleCmdBackwards) {
  EXPECT_TRUE(cmd.Call(GenEraseParam({"erase", "4", "-5"})));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 5; lba++) {
    CheckErased(lba);
  }
  for (unsigned int lba = 5; lba < 100; lba++) {
    CheckPreset(lba);
  }
}

TEST_F(EraseTestFixture, EraseMultiCmd) {
  EXPECT_TRUE(cmd.Call(GenEraseParam({"erase", "0", "11"})));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 11; lba++) {
    CheckErased(lba);
  }
  for (unsigned int lba = 11; lba < 100; lba++) {
    CheckPreset(lba);
  }
}

TEST_F(EraseTestFixture, EraseMultiCmdBackwards) {
  EXPECT_TRUE(cmd.Call(GenEraseParam({"erase", "20", "-15"})));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 6; lba++) {
    CheckPreset(lba);
  }
  for (unsigned int lba = 6; lba < 21; lba++) {
    CheckErased(lba);
  }
  for (unsigned int lba = 21; lba < 100; lba++) {
    CheckPreset(lba);
  }
}

TEST_F(EraseTestFixture, EraseFull) {
  EXPECT_TRUE(cmd.Call(GenEraseParam({"erase", "0", "100"})));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 100; lba++) {
    CheckErased(lba);
  }
}

TEST_F(EraseTestFixture, EraseFullBackwards) {
  EXPECT_TRUE(cmd.Call(GenEraseParam({"erase", "99", "-100"})));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 100; lba++) {
    CheckErased(lba);
  }
}

TEST_F(EraseTestFixture, EraseFullOverRange) {
  EXPECT_TRUE(cmd.Call(GenEraseParam({"erase", "0", "300"})));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 100; lba++) {
    CheckErased(lba);
  }
}

TEST_F(EraseTestFixture, EraseFullOverRangeBackwards) {
  EXPECT_TRUE(cmd.Call(GenEraseParam({"erase", "99", "-300"})));
  EXPECT_TRUE(CheckSuccess());

  for (unsigned int lba = 0; lba < 100; lba++) {
    CheckErased(lba);
  }
}
