#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "gmock/gmock.h"

#define TEST_SHELL_APP_NAME "shell.exe"
#define TEMP_INPUT_FILE_NAME "input.txt"

using namespace testing;

class TestShell {
 public:
  virtual std::string Exec(const std::vector<std::string>& commands) {
    std::string ret;

    std::ostringstream oss;
    auto backupStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    std::ofstream inputFile(TEMP_INPUT_FILE_NAME);
    if (!inputFile) {
      std::cout.rdbuf(backupStreamBuf);
      return "Failed to open temporary input file";
    }

    for (auto command : commands) {
      inputFile << command << std::endl;
    }
    inputFile.close();

    FILE* pipe = _popen(TEST_SHELL_APP_NAME " < " TEMP_INPUT_FILE_NAME, "r");
    if (pipe != nullptr) {
      char buffer[256];
      while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        std::cout << buffer;
      }
      _pclose(pipe);
    }

    std::remove(TEMP_INPUT_FILE_NAME);
    std::cout.rdbuf(backupStreamBuf);
    return oss.str();
  }
};

class MockTestShell : public TestShell {
 public:
  MOCK_METHOD(std::string, Exec, (const std::vector<std::string>&), (override));
};

class TestShellFixture : public Test {
 public:
  MockTestShell mockShell;
  TestShell shell;

  std::vector<std::string> startAndExit = {"exit"};
  std::string startAndExitResult = {"Shell> exit\n Shutting down\n"};
};

TEST_F(TestShellFixture, mockStartAndExit) {
  EXPECT_CALL(mockShell, Exec(_)).WillRepeatedly(Return(startAndExitResult));
  std::string result = mockShell.Exec(startAndExit);
  EXPECT_EQ(startAndExitResult, result);
}

// This test will remain disabled until both the Shell project can be run as a
// shell.exe program.
TEST_F(TestShellFixture, DISABLED_StartAndExit) {
  std::string result = shell.Exec(startAndExit);
  EXPECT_EQ(startAndExitResult, result);
}