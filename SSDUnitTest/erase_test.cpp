#include <gtest/gtest.h>

#include "../SSD/EraseCommand.h"

class FixtureEraseCommand : public ::testing::Test {
 public:
  EraseParam MakeEraseParam(unsigned int lba, unsigned int size) {
    LBA lbaObj = {lba};
    SIZE_E sizeeObj = {size};
    return EraseParam(CMD_TYPE::eEraseCmd, lbaObj, sizeeObj);
  }

  EraseCommand eraseCommand;
};

TEST_F(FixtureEraseCommand, erase_command_success) {
  EraseParam& eraseParam = MakeEraseParam(1, 1);
  bool ret = eraseCommand.Execute(&eraseParam);

  EXPECT_EQ(ret, true);

  eraseParam = MakeEraseParam(95, 5);
  ret = eraseCommand.Execute(&eraseParam);

  EXPECT_EQ(ret, true);
}

TEST_F(FixtureEraseCommand, erase_command_invalidLBA) {
  EraseParam& eraseParam = MakeEraseParam(140, 1);
  bool ret = eraseCommand.Execute(&eraseParam);

  EXPECT_EQ(ret, false);
}

TEST_F(FixtureEraseCommand, erase_command_invalidSize1) {
  EraseParam& eraseParam = MakeEraseParam(1, 12);
  bool ret = eraseCommand.Execute(&eraseParam);

  EXPECT_EQ(ret, false);
}

TEST_F(FixtureEraseCommand, erase_command_invalidSize2) {
  EraseParam& eraseParam = MakeEraseParam(96, 5);
  bool ret = eraseCommand.Execute(&eraseParam);

  EXPECT_EQ(ret, false);
}
