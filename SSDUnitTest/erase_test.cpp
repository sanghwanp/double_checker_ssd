#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "../SSD/CommandBufferHandler.h"
#include "../SSD/CommandFactory.h"
#include "../SSD/FileDriver.h"
#include "../SSD/Types.h"
#include "../SSD/eraseCommand.h"

class MockFileDriver : public FileDriver {
 public:
  MOCK_METHOD(void, SetBufferData, (), ());
  MOCK_METHOD(void, StoreData, (), ());
};

class MockCommandFactory : public CommandFactory {
 public:
  MOCK_METHOD(std::unique_ptr<ICommand>, CreateEraseCommand, (), ());
};

class MockCommandBufferHandler : public CommandBufferHandler {
 public:
  MOCK_METHOD(bool, CheckBufferFull, (), ());
  MOCK_METHOD(std::vector<CommandBufferEntry>, AddErase, (unsigned int lba, unsigned int data), ());
};

class FixtureEraseCommand : public ::testing::Test {
 public:
  EraseParam MakeEraseParam(unsigned int lba, unsigned int size) {
    LBA lbaObj = {lba};
    SIZE_E sizeeObj = {size};
    return EraseParam(CMD_TYPE::eEraseCmd, lbaObj, sizeeObj);
  }
  std::unique_ptr<MockFileDriver> mockFileDriver = std::make_unique<MockFileDriver>();
  std::unique_ptr<MockCommandFactory> mockCommandFactory = std::make_unique<MockCommandFactory>();
  std::unique_ptr<MockCommandBufferHandler> mockBufferHandler = std::make_unique<MockCommandBufferHandler>();

  std::unique_ptr<ICommand> eraseCommand;

  void SetUp() override {
    eraseCommand = std::make_unique<EraseCommand>(mockFileDriver.get(), mockBufferHandler.get(), mockCommandFactory.get());
  }
};

TEST_F(FixtureEraseCommand, erase_command_success) {
  EraseParam& eraseParam = MakeEraseParam(1, 1);
  bool ret = eraseCommand->Execute(&eraseParam);

  EXPECT_EQ(ret, true);

  eraseParam = MakeEraseParam(95, 5);
  ret = eraseCommand->Execute(&eraseParam);

  EXPECT_EQ(ret, true);
}

TEST_F(FixtureEraseCommand, erase_command_invalidLBA) {
  EraseParam& eraseParam = MakeEraseParam(140, 1);
  bool ret = eraseCommand->Execute(&eraseParam);

  EXPECT_EQ(ret, false);
}

TEST_F(FixtureEraseCommand, erase_command_invalidSize1) {
  EraseParam& eraseParam = MakeEraseParam(1, 12);
  bool ret = eraseCommand->Execute(&eraseParam);

  EXPECT_EQ(ret, false);
}

TEST_F(FixtureEraseCommand, erase_command_invalidSize2) {
  EraseParam& eraseParam = MakeEraseParam(96, 5);
  bool ret = eraseCommand->Execute(&eraseParam);

  EXPECT_EQ(ret, false);
}
