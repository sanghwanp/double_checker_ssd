#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "../SSD/CommandBufferHandler.h"
#include "../SSD/CommandFactory.h"
#include "../SSD/FileDriver.h"
#include "../SSD/ReadCommand.h"
#include "../SSD/Types.h"

class MockFileDriver : public FileDriver {
 public:
  MOCK_METHOD(void, SetBufferData, (unsigned int lba, unsigned int data), ());
  MOCK_METHOD(void, GetBufferData, (unsigned int& data), ());
  MOCK_METHOD(void, StoreOutput, (unsigned int val), ());
};

class MockCommandFactory : public CommandFactory {
 public:
  MOCK_METHOD(std::unique_ptr<ICommand>, CreateReadCommand, (), ());
};

class MockCommandBufferHandler : public CommandBufferHandler {
 public:
  MOCK_METHOD(bool, TryFastRead, (unsigned int lba, unsigned int& out_value),
              ());
};

class FixtureReadCommand : public ::testing::Test {
 public:
  ReadParam MakeReadParam(unsigned int lba) {
    LBA lbaObj = {lba};
    return ReadParam(CMD_TYPE::eReadCmd, lbaObj);
  }

  std::unique_ptr<MockFileDriver> mockFileDriver = std::make_unique<MockFileDriver>();
  std::unique_ptr<MockCommandFactory> mockCommandFactory = std::make_unique<MockCommandFactory>();
  std::unique_ptr<MockCommandBufferHandler> mockBufferHandler = std::make_unique<MockCommandBufferHandler>();

  std::unique_ptr<ICommand> readCommand;
  void SetUp() override {
    readCommand = std::make_unique<ReadCommand>(mockFileDriver.get(), mockBufferHandler.get(), mockCommandFactory.get());
  }
};

TEST_F(FixtureReadCommand, Execute_ValidLBA) {
  // arrage
  ReadParam& readParam = MakeReadParam(5);

  // Execute the read command
  bool ret = readCommand->Execute(&readParam);

  EXPECT_EQ(ret, true);
}

TEST_F(FixtureReadCommand, Execute_InvalidLBA) {
  // Prepare an invalid ReadParam
  ReadParam& readParam = MakeReadParam(140);

  // Execute the read command
  bool ret = readCommand->Execute(&readParam);

  EXPECT_EQ(ret, false);
}
