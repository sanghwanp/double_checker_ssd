#include "../SSD/Write.h"

#include "gmock/gmock.h"

using namespace testing;
typedef unsigned int uint;

class WriteCmdMock : public WriteCmd {
 public:
  MOCK_METHOD(void, Init, (), ());
  MOCK_METHOD(void, Init, (), ());
  /*void Init() {
    memset(nand, 0x0, NAND_SIZE);
    first = false;
  }*/
  bool CheckFirst() { return first; }

  bool first{true};
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

  uint GetData(int lba) { return mock.nand[lba]; }

  Command cmd;
  WriteCmdMock mock;
};

TEST_F(WriteTestFixture, 01_Parse_Write_Cmd) {
  cmd.Parse(BASIC_CMD);

  EXPECT_EQ(cmd.cmdType, WRITE);
  EXPECT_EQ(cmd.lba, LBA);
  EXPECT_EQ(cmd.data, DATA);
}

TEST_F(WriteTestFixture, 02_Invalid_Cmd) {
  EXPECT_THROW({ cmd.Parse(INVALID_CMD_TYPE); }, std::invalid_argument);
  EXPECT_THROW({ cmd.Parse(INVALID_CMD_LBA); }, std::invalid_argument);
  EXPECT_THROW({ cmd.Parse(INVALID_CMD_DATA); }, std::invalid_argument);
}

TEST_F(WriteTestFixture, 03_Write_Data_First) {
  if (mock.CheckFirst()) {
    //Init();
  }

  //EXPECT_EQ(GetData(cmd.lba), INIT_DATA);
}

TEST_F(WriteTestFixture, 04_Write_Data_First_MakeFile) {
  //EXPECT_CALL(mock, Init).Times(1);
  cmd.Parse(BASIC_CMD);
  mock.Run(cmd);

  EXPECT_EQ(GetData(cmd.lba), DATA);
}