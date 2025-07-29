#include <iostream>

#include "gmock/gmock.h"
using namespace testing;
using namespace std;

class WriteTestFixture : public Test {
 public:
  const int WRITE = 1;
  const int LBA = 1;
  const int DATA = 0x0;
};

struct Command {
  int cmdType{0};
  int lba{0};
  unsigned int data{0};
};

TEST_F(WriteTestFixture, 01_Parse_Write_Cmd) {
  string cmdStr = "W 1 0x00000000";
  Command cmd;

  std::istringstream iss(cmdStr);
  char type;
  std::string dataStr;

  iss >> type >> cmd.lba >> dataStr;

  // Set cmdType: W = 1, R = 0
  if (type == 'W') {
    cmd.cmdType = 1;
    cmd.data = std::stoul(dataStr, nullptr, 16);  // hex parsing
  } else {
    throw std::invalid_argument("Invalid command type");
  }

  EXPECT_EQ(cmd.cmdType, WRITE);
  EXPECT_EQ(cmd.lba, LBA);
  EXPECT_EQ(cmd.data, DATA);
}