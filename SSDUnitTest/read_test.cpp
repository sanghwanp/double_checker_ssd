#include <gtest/gtest.h>

#include "../SSD/ReadCommand.h"
#include "../SSD/SSD.h"


TEST(ReadCommandTest, Execute_ValidLBA) {

  // arrage
  // Prepare a valid ReadParam
  LBA lba = {5};
  DATA data(0x12345678);

  ReadParam readParam(CMD_TYPE::eReadCmd, lba);

  // Execute the read command
  ReadCommand readCommand;
  bool ret = readCommand.Execute(&readParam);

  EXPECT_EQ(ret, true);
}

TEST(ReadCommandTest, Execute_InvalidLBA) {

  // Prepare an invalid ReadParam
  LBA lba = {140};  // Assuming this is out of bounds
  ReadParam readParam(CMD_TYPE::eReadCmd, lba);

  // Execute the read command
  ReadCommand readCommand;
  bool ret = readCommand.Execute(&readParam);

  EXPECT_EQ(ret, false);
}
