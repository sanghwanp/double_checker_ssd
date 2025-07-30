#include <fstream>
#include <iostream>
#include <stdexcept>

#include "../SSD/IArguments.h"
#include "../SSD/ReadArguments.h"
#include "../SSD/SSD.h"
#include "gmock/gmock.h"

using namespace testing;

class ReadTestFixture : public Test {
 public:
  const int INIT_DATA = 0x00000000;
  const std::string BASIC_ARGS = "R 0";
  const std::string INVALID_ARGS_TYPE = "F 0";
  const std::string INVALID_ARGS_LBA = "R 100";
  const std::string INVALID_ARGS_COUNT = BASIC_ARGS + " 1";

  ReadArguments readArgs;
  SSD ssd;

  const std::string SSD_NAND_TXT_FILEPATH = "C:\\ssd_nand.txt";

  bool DoesFileExist(const std::string &fileName) {
    std::ifstream ifs;
    ifs.open(fileName);
    if (ifs.is_open()) {
      ifs.close();
      return true;
    }
    return false;
  }

  void CreateFile(const std::string &fileName) {
    std::ofstream ofs;
    ofs.open(fileName);
    if (ofs.is_open()) {
      for (int i = 0; i < ReadArguments::LBA_SIZE(); i++) ofs << "0x00000000\n";
      ofs.close();
      return;
    }

    throw std::runtime_error("cannot create ssd_nand.txt file.");
  }
};

class WriteCmdMock : public ICmd {
 public:
  MOCK_METHOD(unsigned int, Run, (IArguments * args), (override));
};

TEST_F(ReadTestFixture, TC01_Read_ThrowException_WhenInvalidArgsType) {
  EXPECT_THROW({ readArgs.Parse(INVALID_ARGS_TYPE); }, std::invalid_argument);
}

TEST_F(ReadTestFixture, TC02_Read_ReturnStoredValue_WhenWrittenBefore) {
  readArgs.Parse(BASIC_ARGS);
  ReadCmd readCmd;
  ssd.SetReadCmd(&readCmd);

  unsigned int data = ssd.Read(&readArgs);
  EXPECT_EQ(data, INIT_DATA);
}

TEST_F(ReadTestFixture, TC03_Read_ThrowException_WhenIvalidArgsLba) {
  EXPECT_THROW({ readArgs.Parse(INVALID_ARGS_LBA); }, std::invalid_argument);
}

TEST_F(ReadTestFixture, TC04_Read_ThrowException_WhenIvalidArgsCount) {
  EXPECT_THROW({ readArgs.Parse(INVALID_ARGS_COUNT); }, std::invalid_argument);
}

TEST_F(ReadTestFixture, TC05_Read_ReturnStoredValue_WhenWrittenAfter) {
  WriteCmdMock mock;
  ReadCmd readCmd;
  SSD ssd;

  ssd.SetWriteCmd(&mock);
  ssd.SetReadCmd(&readCmd);

  std::ostringstream oss;
  for (int data = 0; data < 5; data++) {
    WriteArguments writeArgs;
    writeArgs.Parse("W " + std::to_string(data) + " 0x" +
                    (std::stringstream()
                     << std::hex << std::setw(8) << std::setfill('0') << data)
                        .str());

    EXPECT_CALL(mock, Run(&writeArgs)).WillOnce([&]() {
      if (false == DoesFileExist(SSD_NAND_TXT_FILEPATH)) {
        CreateFile(SSD_NAND_TXT_FILEPATH);
      }

      std::ifstream ifs(SSD_NAND_TXT_FILEPATH);
      const int MAX_LBA_SIZE = 100;
      std::vector<unsigned int> cache(MAX_LBA_SIZE, 0);
      for(int lba=0; lba<MAX_LBA_SIZE; lba++) {
          ifs >> std::hex >> cache[lba];
      }

      const int lbaToWrite = data;
      cache[lbaToWrite] = data;

      std::ofstream ofs;
      ofs.open(SSD_NAND_TXT_FILEPATH);
      for (int i = 0; i < cache.size(); i++) {
        ofs << std::hex << cache[i] << "\n";
      }
      ofs.close();

      const int kVoidResult = 0;
      return kVoidResult;
    });
    ssd.Write(&writeArgs);
  }

  for (unsigned int i = 0; i < 5; i++) {
    ReadArguments readArgs;
    readArgs.Parse("R " + std::to_string(i));
    unsigned int result = ssd.Read(&readArgs);
    EXPECT_EQ(result, i);
  }
}
