#include <gmock/gmock.h>
#include "../Shell/ILogFileSystem.h"
#include "../Shell/Logger.h"

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


TEST(LoggerTest, RotatesLogFileWhenSizeExceedsMax) {
  using namespace std;
  using namespace testing;
  using namespace std::filesystem;

  // Arrange
  auto mockFS = new NiceMock<MockFileSystem>();
  Logger logger(mockFS, true);

  const std::string logFileName = "latest.log";
  const std::filesystem::path logFilePath(logFileName);

  EXPECT_CALL(*mockFS, Exists(logFilePath)).WillOnce(Return(true));
  EXPECT_CALL(*mockFS, File_size(logFilePath))
      .WillOnce(Return(11 * 1024));             // 11KB
  EXPECT_CALL(*mockFS, Rename(_, _)).Times(1);  // rotated name
  EXPECT_CALL(*mockFS, ListFiles((std::filesystem::path) "."))
      .WillOnce(Return(std::vector<directory_entry>{}));  // skip manageOldLogs

  // Act
  logger.Print("RotateTestFunc", "Trigger log rotation by exceeding file size");
}

TEST(LoggerTest, ConsoleOutputDisabled_DoesNotPrintToConsole) {
  testing::NiceMock<MockFileSystem> mockFS;
  Logger logger(&mockFS, true);
  logger.SetConsoleOutput(false);

  // std::cout 캡쳐 또는 Redirect 필요 (예: testing::internal::CaptureStdout())
  testing::internal::CaptureStdout();
  logger.Print("Func", "Message");
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(output.empty());
}

TEST(LoggerTest, EndsWithFunction_WorksCorrectly) {
  Logger logger;
  ILogger* loggerPtr = &logger;

  logger.Print("TestFunc()", "Testing ends_with function");
  loggerPtr->Print("TestFunc()", "Testing ends_with function from interface");
}

//TEST(LoggerTest, loggerPrint_10000) {
//  Logger logger;
//  ILogger* loggerPtr = &logger;
//
//  int loopCnt = 10000;
//  for (int i = 0; i < loopCnt; i++) {
//    loggerPtr->print("TestFunc", "Testing ends_with function");
//  }
//}
