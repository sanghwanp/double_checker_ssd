#include "../SSD/SSD.h"
#include "../SSD/WriteCommand.h"
#include "../SSD/WriteArguments.h"
#include "gmock/gmock.h"

using namespace testing;
typedef unsigned int uint;

class MockWriteArguments : public WriteArguments {
 public:
  MOCK_METHOD(unsigned int, GetLba, (), (const, override));
  //MOCK_METHOD(unsigned int, GetCachedData, (), (const));
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

  SSD ssd;
  WriteCommand writeCmd;
  WriteArguments writeArgs;

  void SetUp() override {
	  ssd.SetWriteCmd(&writeCmd);
  }

  unsigned int GetCachedData(int lba) { 
	  return ssd.GetCachedData(lba); 
  }
};

TEST_F(WriteTestFixture, 01_Parse_Write_Cmd) {
  writeArgs.Parse(BASIC_CMD);

  // EXPECT_EQ(args.cmdType, WRITE);
  EXPECT_EQ(writeArgs.GetLba(), LBA);
  EXPECT_EQ(writeArgs.GetCachedData(), DATA);
}

TEST_F(WriteTestFixture, 02_Invalid_Cmd) {
  EXPECT_THROW({ writeArgs.Parse(INVALID_CMD_TYPE); }, std::invalid_argument);
  EXPECT_THROW({ writeArgs.Parse(INVALID_CMD_LBA); }, std::invalid_argument);
  EXPECT_THROW({ writeArgs.Parse(INVALID_CMD_DATA); }, std::invalid_argument);
  EXPECT_THROW({ writeArgs.Parse(INVALID_CMD_1); }, std::invalid_argument);
  EXPECT_THROW({ writeArgs.Parse(INVALID_CMD_2); }, std::invalid_argument);
  EXPECT_THROW({ writeArgs.Parse(INVALID_CMD_3); }, std::invalid_argument);
}

TEST_F(WriteTestFixture, 03_Write_Data_First) {
  writeArgs.Parse(BASIC_CMD);
  ssd.Write(&writeArgs);
  //writeCmd.Run(&args);

  EXPECT_EQ(GetCachedData(writeArgs.GetLba()), DATA);
}
