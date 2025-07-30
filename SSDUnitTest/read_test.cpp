#include <stdexcept>

#include "../SSD/ReadArguments.h"
#include "../SSD/SSD.h"
#include "gmock/gmock.h"

using namespace testing;

class ReadTestFixture : public Test {
 public:
  const int READ = 2;
  const int LBA = 0;
  const int INIT_DATA = 0x00000000;
  const std::string BASIC_ARGS = "R 0";
  const std::string INVALID_ARGS_TYPE = "F 0";
  const std::string INVALID_ARGS_LBA = "R 100";
  const std::string INVALID_ARGS_DATA = BASIC_ARGS + " 1";

  ReadArguments readArgs;
  SSD ssd;
  void ParsingArgs(const std::string &args) { readArgs.Parse(args); }
};

TEST_F(ReadTestFixture, TC01_Read_ThrowException_WhenInvalidArgsType) {
  EXPECT_THROW({ ParsingArgs(INVALID_ARGS_TYPE); }, std::invalid_argument);
}

TEST_F(ReadTestFixture, TC02_Read_ReturnStoredValue_WhenWrittenBefore) {
  ParsingArgs(BASIC_ARGS);

  unsigned int data = ssd.Read(readArgs.GetLba());
  EXPECT_EQ(data, INIT_DATA);
}
