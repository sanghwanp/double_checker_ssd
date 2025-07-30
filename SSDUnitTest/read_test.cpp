#include <stdexcept>

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
  void ParsingArgs(const std::string &args) { readArgs.ParseAndValidate(args); }
};

class WriteCmdMock: public ICmd {
	MOCK_METHOD(void, Run, (unsigned int lba, int hexaData), ());
};

TEST_F(ReadTestFixture, TC01_Read_ThrowException_WhenInvalidArgsType) {
  EXPECT_THROW({ ParsingArgs(INVALID_ARGS_TYPE); }, std::invalid_argument);
}

TEST_F(ReadTestFixture, TC02_Read_ReturnStoredValue_WhenWrittenBefore) {
  //ParsingArgs(BASIC_ARGS);
  readArgs.ParseAndValidate(BASIC_ARGS);

  unsigned int data = ssd.Read(readArgs);
  EXPECT_EQ(data, INIT_DATA);
}

TEST_F(ReadTestFixture, TC03_Read_ThrowException_WhenIvalidArgsLba) {
  EXPECT_THROW({ ParsingArgs(INVALID_ARGS_LBA); }, std::invalid_argument);
}

TEST_F(ReadTestFixture, TC04_Read_ThrowException_WhenIvalidArgsCount) {
  EXPECT_THROW({ ParsingArgs(INVALID_ARGS_COUNT); }, std::invalid_argument);
}

//TEST_F(ReadTestFixture, TC05_Read_ReturnStoredValue_WhenWrittenAfter) {
//	WriteCmdMock mock;
//	SSD ssd(&mock);
//	//ICmd cmd(&mock);
//	EXPECT_CALL(mock, Run(1,0x2))
//		WillReturn
//}
