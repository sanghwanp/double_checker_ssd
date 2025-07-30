#include "../SSD/WriteCmd.h"
#include "gmock/gmock.h"

using namespace testing;
typedef unsigned int uint;

class WriteCmdMock : public WriteCmd {
 public:
  // MOCK_METHOD(void, Init, (), ());
  // MOCK_METHOD(bool, CheckFirst, (), ());
};

class WriteTestFixture : public Test {
 public:
  const int WRITE = 1;
  const int LBA = 1;
  const int DATA = 0x10;
  const int INIT_DATA = 0x0;
  const std::string BASIC_CMD = "W 1 0x00000010";
  const std::string INVALID_CMD_TYPE = "F 1 0x00000000";
  const std::string INVALID_CMD_LBA = "W 100 0x00000000";
  const std::string INVALID_CMD_DATA = "W 1 0x100000000";
  const std::string INVALID_CMD_1 = "1 1 0x100000000";
  const std::string INVALID_CMD_2 = "W W 0x100000000";
  const std::string INVALID_CMD_3 = "W 1 0xxxxxxxxx";

  uint GetData(int lba) { return mock.nand[lba]; }

  CommandArguments cmd;
  WriteCmdMock mock;
};

TEST_F(WriteTestFixture, TC01_Parse_Write_Cmd) {
  cmd.Parse(BASIC_CMD);

  EXPECT_EQ(cmd.cmdType, WRITE);
  EXPECT_EQ(cmd.lba, LBA);
  EXPECT_EQ(cmd.data, DATA);
}

TEST_F(WriteTestFixture, TC02_Invalid_Cmd) {
  EXPECT_THROW({ cmd.Parse(INVALID_CMD_TYPE); }, std::invalid_argument);
  EXPECT_THROW({ cmd.Parse(INVALID_CMD_LBA); }, std::invalid_argument);
  EXPECT_THROW({ cmd.Parse(INVALID_CMD_DATA); }, std::invalid_argument);
  EXPECT_THROW({ cmd.Parse(INVALID_CMD_1); }, std::invalid_argument);
  EXPECT_THROW({ cmd.Parse(INVALID_CMD_2); }, std::invalid_argument);
  EXPECT_THROW({ cmd.Parse(INVALID_CMD_3); }, std::invalid_argument);
}

TEST_F(WriteTestFixture, TC03_Write_Data_First) {
  // EXPECT_CALL(mock, CheckFirst).Times(1).WillOnce(Return(true));
  // EXPECT_CALL(mock, Init).Times(1);
  mock.Init();
  EXPECT_EQ(GetData(LBA), INIT_DATA);

  cmd.Parse(BASIC_CMD);
  mock.Run(cmd);

  EXPECT_EQ(GetData(cmd.lba), DATA);
}
