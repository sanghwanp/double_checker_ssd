#include <iostream>
#include <sstream>
#include <unordered_map>

#include "../Shell/CmdFullRead.h"
#include "../Shell/MockSSD.h"
#include "../Shell/Parser.h"
#include "gTestCommandCallCommon.h"
#include "gmock/gmock.h"

using namespace testing;

class FullReadTestFixture : public CommandCallCommon {
 public:
  void SetUp() override {
    oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
  }

  void TearDown() override { std::cout.rdbuf(oldCoutStreamBuf); }

  std::string GetCoutStr() { return oss.str(); }

  std::string GetExpectedStr(
      const std::unordered_map<int, std::string> values = {}) {
    std::ostringstream ossExpected;
    for (unsigned int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
      ossExpected << COUT_HEADER << std::setfill('0') << std::setw(2) << lba
                  << " : ";

      auto it = values.find(lba);
      if (it == values.end()) {
        ossExpected << INIT_VALUE << "\n";
      } else {
        auto value = it->second;
        ossExpected << value << "\n";
      }
    }

    return ossExpected.str();
  }

  std::ostringstream oss;
  std::streambuf* oldCoutStreamBuf;

  MockSSD ssd;
  CommandFullRead cmd{&ssd};

 private:
  const unsigned int MIN_LBA = 0;
  const unsigned int MAX_LBA = 99;
  const char* INIT_VALUE = "0x00000000";
  const char* COUT_HEADER = "[Fullread] LBA ";
};

TEST_F(FullReadTestFixture, FullReadDefault) {
  EXPECT_TRUE(cmd.Call(GenParam("fullread")));

  std::string outputStr = GetCoutStr();
  EXPECT_EQ(GetExpectedStr(), outputStr);
}

TEST_F(FullReadTestFixture, FullReadValue) {
  ssd.Write(1, "0x12345678");
  ssd.Write(5, "0x3456789A");

  EXPECT_TRUE(cmd.Call(GenParam("fullread")));

  std::string outputStr = GetCoutStr();
  EXPECT_EQ(GetExpectedStr({{1, "0x12345678"}, {5, "0x3456789A"}}), outputStr);
}

TEST_F(FullReadTestFixture, FullReadInvalid) {
  EXPECT_FALSE(cmd.Call(GenParam("read")));
}
