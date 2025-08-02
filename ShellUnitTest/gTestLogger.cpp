#include <gmock/gmock.h>
#include "../Shell/ILogFileSystem.h"
#include "../Shell/Logger.h"

using namespace testing;
class MockFileSystem : public ILogFileSystem {
 public:
  MOCK_METHOD(bool, Exists, (const std::filesystem::path&), (const, override));
  MOCK_METHOD(std::uintmax_t, File_size, (const std::filesystem::path&),
              (const, override));
  MOCK_METHOD(std::vector<std::filesystem::directory_entry>, ListFiles,
              (const std::filesystem::path&), (const, override));
  MOCK_METHOD(bool, IsRegularFile, (const std::filesystem::directory_entry&),
              (const, override));
  MOCK_METHOD(std::string, FileName, (const std::filesystem::directory_entry&),
              (const, override));
  MOCK_METHOD(std::filesystem::file_time_type, LastWriteTime,
              (const std::filesystem::directory_entry&), (const, override));
  MOCK_METHOD(void, Rename,
              (const std::filesystem::path&, const std::filesystem::path&),
              (override));
};

class LoggerTestFixture : public ::testing::Test {
 protected:
  void SetUp() override {
    logger.SetLoggerFileSystem(&mockFS);
    logger.SetConsoleOutput(true);
  }
  
  void TearDown() override {

    logger.RestoreLoggerFileSystem();
  }
  Logger& logger = Logger::GetInstance();
  NiceMock<MockFileSystem> mockFS;
  
};


TEST_F(LoggerTestFixture, RotatesLogFileWhenSizeExceedsMax) {
  using namespace std;
  using namespace testing;
  using namespace std::filesystem;

  // Arrange
  const std::string logFileName = "latest.log";
  const std::filesystem::path logFilePath(logFileName);

  EXPECT_CALL(mockFS, Exists(logFilePath)).WillOnce(Return(true));
  EXPECT_CALL(mockFS, File_size(logFilePath))
      .WillOnce(Return(11 * 1024));             // 11KB
  EXPECT_CALL(mockFS, Rename(_, _)).Times(1);  // rotated name
  EXPECT_CALL(mockFS, ListFiles((std::filesystem::path) "."))
      .WillOnce(Return(std::vector<directory_entry>{}));  // skip manageOldLogs

  // Act
  logger.LogPrint("RotateTestFunc", "Trigger log rotation by exceeding file size");
}

TEST_F(LoggerTestFixture, ConsoleOutputDisabled_DoesNotPrintToConsole) {

  logger.SetConsoleOutput(false);
  testing::internal::CaptureStdout();
  logger.LogPrint("Func", "Message");
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(output.empty());
}

TEST_F(LoggerTestFixture, EndsWithFunction_WorksCorrectly) {
  ILogger* loggerPtr = &logger;

  logger.LogPrint("TestFunc()", "Testing ends_with function");
  loggerPtr->LogPrint("TestFunc()", "Testing ends_with function from interface");
}

TEST_F(LoggerTestFixture, Call_ILogger) {
  testing::internal::CaptureStdout();

  ILogger::GetInstance()->LogPrint("TestFunc()", "ILogger::GetInstance().LogPrint");
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(output.size() > 30);
}


//TEST(LoggerTest, loggerPrint_10000) {
//  ILogger* loggerPtr = new Logger;
//
//  int loopCnt = 10000;
//  for (int i = 0; i < loopCnt; i++) {
//    loggerPtr->LogPrint("TestFunc", "Testing ends_with function");
//  }
//}
