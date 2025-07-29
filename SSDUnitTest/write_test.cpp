#include <iostream>

#include "gmock/gmock.h"
using namespace testing;
typedef unsigned int uint;

const int MAX_LBA = 99;
const int MAX_DATA_LEN = 10;

class WriteTestFixture : public Test {
 public:
  const int WRITE = 1;
  const int LBA = 1;
  const int DATA = 0x0;
  const std::string BASIC_CMD = "W 1 0x00000000";
  const std::string INVALID_CMD_TYPE = "F 1 0x00000000";
  const std::string INVALID_CMD_LBA = "W 100 0x00000000";
  const std::string INVALID_CMD_DATA = "W 1 0x100000000";
};

struct Command {
  int cmdType;
  int lba;
  uint data;
  std::istringstream iss;
  std::string typeStr;
  std::string dataStr;

  Command() : cmdType{0}, lba{0}, data{0} {}
  Command(int t, int l, uint d) : cmdType{t}, lba{l}, data{d} {}

  bool CheckErrorCmd() {
    if (typeStr != "W") {
      return true;
    }
    if (lba < 0 || lba > MAX_LBA) {
      return true;
    }
    if (dataStr.length() > MAX_DATA_LEN) {
      return true;
    }
    return false;
  }

  void Parse(std::string cmdStr) {
    iss = std::istringstream(cmdStr);
    iss >> typeStr >> lba >> dataStr;

    if (CheckErrorCmd()) throw std::invalid_argument("Invalid command type");

    cmdType = 1;
    data = std::stoul(dataStr, nullptr, 16);  // hex parsing
  }
};

TEST_F(WriteTestFixture, 01_Parse_Write_Cmd) {
  Command cmd;
  cmd.Parse(BASIC_CMD);

  EXPECT_EQ(cmd.cmdType, WRITE);
  EXPECT_EQ(cmd.lba, LBA);
  EXPECT_EQ(cmd.data, DATA);
}

TEST_F(WriteTestFixture, 02_Invalid_CmdType) {
  Command cmd;

  EXPECT_THROW({ cmd.Parse(INVALID_CMD_TYPE); }, std::invalid_argument);
}

TEST_F(WriteTestFixture, 03_Invalid_Lba) {
  Command cmd;

  EXPECT_THROW({ cmd.Parse(INVALID_CMD_LBA); }, std::invalid_argument);
}

TEST_F(WriteTestFixture, 04_Invalid_Data) {
  Command cmd;

  EXPECT_THROW({ cmd.Parse(INVALID_CMD_DATA); }, std::invalid_argument);
}