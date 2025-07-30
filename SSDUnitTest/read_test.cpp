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
};

#if 0 //[RED] ??? -- main? merge? ?? ?? off
class WriteCmdMock : public ICmd {
  MOCK_METHOD(void, Run, (WriteArguments*), (override));
};
#endif

TEST_F(ReadTestFixture, TC01_Read_ThrowException_WhenInvalidArgsType) {
  EXPECT_THROW(
      { readArgs.ParseAndValidate(INVALID_ARGS_TYPE); }, std::invalid_argument);
}

TEST_F(ReadTestFixture, TC02_Read_ReturnStoredValue_WhenWrittenBefore) {
  // readArgs.ParseAndValidate(BASIC_ARGS);
  readArgs.ParseAndValidate(BASIC_ARGS);

  unsigned int data = ssd.Read(readArgs);
  EXPECT_EQ(data, INIT_DATA);
}

TEST_F(ReadTestFixture, TC03_Read_ThrowException_WhenIvalidArgsLba) {
  EXPECT_THROW(
      { readArgs.ParseAndValidate(INVALID_ARGS_LBA); }, std::invalid_argument);
}

TEST_F(ReadTestFixture, TC04_Read_ThrowException_WhenIvalidArgsCount) {
  EXPECT_THROW(
      { readArgs.ParseAndValidate(INVALID_ARGS_COUNT); },
      std::invalid_argument);
}

#if 0 //[RED] ??? -- main? merge? ?? ?? off
 TEST_F(ReadTestFixture, TC05_Read_ReturnStoredValue_WhenWrittenAfter) {
  WriteCmdMock mock;
  ReadCmd readCmd;
  SSD ssd;

  ssd.SetWriteCmd(&mock);
  ssd.SetReadCmd(&readCmd);

  std::ostringstream oss;
  for(int i=0; i<5; i++) {
      oss.str("");
      oss.clear();
      oss << "0x"
          << std::uppercase
          << std::hex
          << std::setw(8)
          << std::setfill('0')
          << i;
      const std::string writeArg{ oss.str() };
      WriteArguments writeArgs;
      writeArgs.ParseAndValidate{ writeArg };
      
      EXPECT_CALL(mock, Run(writeArgs)).Return
      
  }

  mock.Run(writeArgs);


  SSD ssd(&readCmd, &mock);
  // ICmd cmd(&mock);
  //EXPECT_CALL(mock, Run(Write)).WillOnce();
 }
#endif
