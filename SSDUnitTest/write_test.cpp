#include <gtest/gtest.h>
#include "../SSD/WriteCommand.h"


class FixtureWriteCommand : public ::testing::Test {
 public:
  WriteParam MakeWriteParam(unsigned int lba, unsigned int data) {
    LBA lbaObj = {lba};
    DATA dataObj = {data};
    return WriteParam(CMD_TYPE::eWriteCmd, lbaObj, dataObj);
  }

  WriteCommand writeCommand;
};

TEST_F(FixtureWriteCommand, write_command_success)
{
  WriteParam& writeParam = MakeWriteParam(1,0x12345678);
  bool ret = writeCommand.Execute(&writeParam, false);

  EXPECT_EQ(ret, true);
}

TEST_F(FixtureWriteCommand, write_command_invalidLBA) {
  WriteParam& writeParam = MakeWriteParam(140, 0x12345678);
  bool ret = writeCommand.Execute(&writeParam, false);

  EXPECT_EQ(ret, false);
}
