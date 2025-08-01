#include <gtest/gtest.h>

#include "../SSD/ReadCommand.h"
#include "../SSD/SSD.h"


class FixtureReadCommand : public ::testing::Test {

  public:
  ReadParam MakeReadParam(unsigned int lba)
  {
     LBA lbaObj = {lba};
     return ReadParam(CMD_TYPE::eReadCmd, lbaObj);
  }
};

TEST_F(FixtureReadCommand, Execute_ValidLBA) {

  // arrage
  ReadParam& readParam = MakeReadParam(5);

  // Execute the read command
  ReadCommand readCommand;
  bool ret = readCommand.Execute(&readParam);

  EXPECT_EQ(ret, true);
}

TEST_F(FixtureReadCommand, Execute_InvalidLBA) {

  // Prepare an invalid ReadParam
  ReadParam& readParam = MakeReadParam(140);

  // Execute the read command
  ReadCommand readCommand;
  bool ret = readCommand.Execute(&readParam);

  EXPECT_EQ(ret, false);
}
