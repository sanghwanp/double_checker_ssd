#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <string>

#include "../SSD/CommandBufferHandler.h"
#include "../SSD/CommandFactory.h"
#include "../SSD/FileDriver.h"
#include "../SSD/Parser.h"
#include "../SSD/SSD.h"

class SSDTest : public ::testing::Test {
 public:
  IParam* MakeParam(CMD_TYPE etype, unsigned int param1 = 0,
                    unsigned int param2 = 0) {
    LBA lbaObj = {param1};
    DATA dataObj = {param2};
    SIZE_E sizeObj = {param2};
    switch (etype) {
      case eReadCmd:
        return new ReadParam(CMD_TYPE::eReadCmd, lbaObj);
        break;
      case eWriteCmd:
        return new WriteParam(CMD_TYPE::eWriteCmd, lbaObj, dataObj);
        break;
      case eEraseCmd:
        return new EraseParam(CMD_TYPE::eEraseCmd, lbaObj, sizeObj);
        break;
      case eFlushCmd:
        return new FlushParam(CMD_TYPE::eFlushCmd);
        break;
      default:
        return new IParam(CMD_TYPE::eInvalidCmd);
        break;
    }
  }

  std::string readOutputFile() {
    std::ifstream file(READ_OUTPUT_FILE_NAME);
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    return content;
  }

  SSD* ssd;

  void SetUp() override {
    FileDriver* fileDriver = FileDriver::GetInstance();
    CommandFactory* commandFactory = CommandFactory::GetInstance();
    CommandBufferHandler* bufferHandler = CommandBufferHandler::GetInstance();

    ssd = &SSD::GetInstance(fileDriver, bufferHandler, commandFactory);
  }

 protected:
  const unsigned int TEST_LBA = 5;
  const unsigned int TEST_DATA = 0x12345678;
  const unsigned int ERASE_DATA = 0;
  const std::string READ_OUTPUT_FILE_NAME = "ssd_output.txt";
};

TEST_F(SSDTest, Flush) {
  // Write
  ssd->Run(MakeParam(eWriteCmd, TEST_LBA, TEST_DATA));

  // Read
  ssd->Run(MakeParam(eReadCmd, TEST_LBA));

  // Flush
  ssd->Run(MakeParam(eFlushCmd));

  // Check cache
  unsigned int cached = ssd->GetCachedData(TEST_LBA);
  EXPECT_EQ(cached, TEST_DATA);
}

TEST_F(SSDTest, Write_6times_check_flush) {
  // Write
  for (int i = 0; i < 6; i++) {
    ssd->Run(MakeParam(eWriteCmd, i, 0xFFFFFFFF));
  }

  // Check cache
}

TEST_F(SSDTest, DIABLED_WriteAndRead_CachedData) {
  // Write
  ssd->Run(MakeParam(eWriteCmd, TEST_LBA, TEST_DATA));

  // Read
  ssd->Run(MakeParam(eReadCmd, TEST_LBA));

  // Check cache
  unsigned int cached = ssd->GetCachedData(TEST_LBA);
  EXPECT_EQ(cached, TEST_DATA);
}
//
TEST_F(SSDTest, WriteAndEraseAndRead_CachedData) {
  // Write
  ssd->Run(MakeParam(eWriteCmd, TEST_LBA, TEST_DATA));

  // Read
  ssd->Run(MakeParam(eReadCmd, TEST_LBA));

  // Check cache
  unsigned int cached = ssd->GetCachedData(TEST_LBA);
  EXPECT_EQ(cached, TEST_DATA);

  // Erase
  ssd->Run(MakeParam(eEraseCmd, TEST_LBA, 1));

  // Read
  ssd->Run(MakeParam(eReadCmd, TEST_LBA));

  // Check cache
  cached = ssd->GetCachedData(TEST_LBA);
  EXPECT_EQ(cached, ERASE_DATA);
}

TEST_F(SSDTest, ReadCommand_InvalidLBA) {
  // Read
  ssd->Run(MakeParam(eReadCmd, 140));

  string output = readOutputFile();

  EXPECT_EQ(output, "ERROR\n");
}

TEST_F(SSDTest, Run_InvalidCommandType) {
  // Write
  ssd->Run(MakeParam(eWriteCmd, TEST_LBA, TEST_DATA));
  // Read
  unsigned int before = ssd->GetCachedData(TEST_LBA);

  // 정상적으로 처리하지 못하면 내부적으로 "Invalid command" 출력
  // 예외는 발생하지 않으나, 캐시에는 변화 없음
  ssd->Run(MakeParam(eInvalidCmd, TEST_LBA));

  unsigned int after = ssd->GetCachedData(TEST_LBA);
  EXPECT_EQ(before, after);
}
