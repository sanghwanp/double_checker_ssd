#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <vector>

#include "../SSD/CommandBufferHandler.h"
#include "../SSD/CommandBufferEntry.h"
#include "../SSD/CommandFactory.h"
#include "../SSD/FileDriver.h"
#include "../SSD/Types.h"
#include "../SSD/WriteCommand.h"

class MockFileDriver : public FileDriver {
 public:
  MOCK_METHOD(void, SetBufferData, (), ());
  MOCK_METHOD(void, StoreData, (), ());
};

class MockCommandFactory : public CommandFactory {
 public:
  MOCK_METHOD(std::unique_ptr<ICommand>, CreateWriteCommand, (), ());
};

class MockCommandBufferHandler : public CommandBufferHandler {
 public:
  MOCK_METHOD(bool, CheckBufferFull, (), ());
  MOCK_METHOD(std::vector<CommandBufferEntry>, AddWrite, (unsigned int lba, unsigned int data), ());
};

class FixtureWriteCommand : public ::testing::Test {
 public:
  WriteParam MakeWriteParam(unsigned int lba, unsigned int data) {
    LBA lbaObj = {lba};
    DATA dataObj = {data};
    return WriteParam(CMD_TYPE::eWriteCmd, lbaObj, dataObj);
  }
  std::unique_ptr<MockFileDriver> mockFileDriver = std::make_unique<MockFileDriver>();
  std::unique_ptr<MockCommandFactory> mockCommandFactory = std::make_unique<MockCommandFactory>();
  std::unique_ptr<MockCommandBufferHandler> mockBufferHandler = std::make_unique<MockCommandBufferHandler>();

  std::unique_ptr<ICommand> writeCommand;

  void SetUp() override {
    writeCommand = std::make_unique<WriteCommand>(mockFileDriver.get(), mockBufferHandler.get(), mockCommandFactory.get());
  }
};

TEST_F(FixtureWriteCommand, write_command_success) {
  WriteParam& writeParam = MakeWriteParam(1, 0x12345678);
  bool ret = writeCommand->Execute(&writeParam);

  EXPECT_EQ(ret, true);
}

TEST_F(FixtureWriteCommand, write_command_invalidLBA) {
  WriteParam& writeParam = MakeWriteParam(140, 0x12345678);
  bool ret = writeCommand->Execute(&writeParam);

  EXPECT_EQ(ret, false);
}
