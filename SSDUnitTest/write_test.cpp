#include "../SSD/WriteCmd.h"
#include "gmock/gmock.h"

using namespace testing;
typedef unsigned int uint;

class MockWriteArguments : public WriteArguments {
 public:
  MOCK_METHOD(unsigned int, GetLba, (), (const, override));
  MOCK_METHOD(unsigned int, GetData, (), (const));
};

class WriteTestFixture : public Test {
 public:
  const int LBA = 1;
  const unsigned int DATA = 0x10;
  const unsigned int INIT_DATA = 0x0;
  const std::string BASIC_CMD = "W 1 0x00000010";
  const std::string INVALID_CMD_TYPE = "F 1 0x00000000";
  const std::string INVALID_CMD_LBA = "W 100 0x00000000";
  const std::string INVALID_CMD_DATA = "W 1 0x100000000";
  const std::string INVALID_CMD_1 = "1 1 0x100000000";
  const std::string INVALID_CMD_2 = "W W 0x100000000";
  const std::string INVALID_CMD_3 = "W 1 0xxxxxxxxx";

  WriteCmd cmd;
  WriteArguments args;

  void SetUp() override { cmd.Init(); }

  unsigned int GetData(int lba) { return cmd.GetData(lba); }
};

TEST_F(WriteTestFixture, 01_Parse_Write_Cmd) {
  args.Parse(BASIC_CMD);

  // EXPECT_EQ(args.cmdType, WRITE);
  EXPECT_EQ(args.GetLba(), LBA);
  EXPECT_EQ(args.GetData(), DATA);
}

#if 0
TEST_F(WriteTestFixture, 02_Invalid_Cmd) {
  EXPECT_THROW({ args.Parse(INVALID_CMD_TYPE); }, std::invalid_argument);
  EXPECT_THROW({ args.Parse(INVALID_CMD_LBA); }, std::invalid_argument);
  EXPECT_THROW({ args.Parse(INVALID_CMD_DATA); }, std::invalid_argument);
  EXPECT_THROW({ args.Parse(INVALID_CMD_1); }, std::invalid_argument);
  EXPECT_THROW({ args.Parse(INVALID_CMD_2); }, std::invalid_argument);
  EXPECT_THROW({ args.Parse(INVALID_CMD_3); }, std::invalid_argument);
}

TEST_F(WriteTestFixture, 03_Write_Data_First) {
  // EXPECT_CALL(mock, CheckFirst).Times(1).WillOnce(Return(true));
  // EXPECT_CALL(mock, Init).Times(1);
  mock.Init();
  EXPECT_EQ(GetData(LBA), INIT_DATA);

  args.Parse(BASIC_CMD);
  mock.Run(args);

  EXPECT_EQ(GetData(args.lba), DATA);
}
#endif
