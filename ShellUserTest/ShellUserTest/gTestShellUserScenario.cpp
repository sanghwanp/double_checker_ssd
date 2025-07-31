#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "gmock/gmock.h"

#define TEST_SHELL_APP_NAME "..\\..\\x64\\debug_TestShell\\Shell.exe"
#define TEMP_INPUT_FILE_NAME "input.txt"
#define SHELL_PREFIX_OUTPUT "Shell> "
#define SHELL_EXIT_OUTPUT SHELL_PREFIX_OUTPUT "Shutting down\n"
#define SHELL_WRITE_DONE_OUTPUT "[Write] Done\n"

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
  void SendCommandToMock(const std::vector<std::string>& command,
                         const std::string& expected) {
    EXPECT_CALL(mockShell, Exec(_)).WillOnce(Return(expected));
    std::string result = mockShell.Exec(command);
    EXPECT_EQ(expected, result);
  }

  void SendCommandToReal(const std::vector<std::string>& command,
                         const std::string& expected) {
    std::string result = shell.Exec(command);
    EXPECT_EQ(expected, result);
  }

  MockTestShell mockShell;
  TestShell shell;
  const int LBA_COUNT = 100;

  // 1
  std::vector<std::string> startAndExit = {"exit"};
  std::string startAndExitResult = {SHELL_EXIT_OUTPUT};

  // 2
  std::vector<std::string> write = {"write 3 0xAAAABBBB", "exit"};
  std::string writeResult = {
      SHELL_PREFIX_OUTPUT SHELL_WRITE_DONE_OUTPUT SHELL_EXIT_OUTPUT};

  // 3
  std::vector<std::string> read = {"read 0", "exit"};
  std::string readResult = {SHELL_PREFIX_OUTPUT
                            "[Read] LBA 00 : 0x00000000\n" SHELL_EXIT_OUTPUT};

  // 4
  std::vector<std::string> writeAndRead = {"write 4 0xAAAABBBB", "read 4",
                                           "exit"};
  std::string writeAndReadResult = {
      SHELL_PREFIX_OUTPUT "[Write] Done\n" SHELL_PREFIX_OUTPUT
                          "[Read] LBA 04 : 0xAAAABBBB\n" SHELL_EXIT_OUTPUT};

  // 5
  std::vector<std::string> fullwrite = {"fullwrite 0xABCDFFFF", "exit"};
  std::string fullwriteResult = {SHELL_PREFIX_OUTPUT
                                 "[Fullwrite] Done\n" SHELL_EXIT_OUTPUT};

  // 6
  std::vector<std::string> fullread = {"fullread", "exit"};
  std::string fullreadResult = {
      SHELL_PREFIX_OUTPUT
      "[Fullread] LBA 00 : 0x00000000\n"
      "[Fullread] LBA 01 : 0x00000000\n"
      "[Fullread] LBA 02 : 0x00000000\n"
      "[Fullread] LBA 03 : 0x00000000\n"
      "[Fullread] LBA 04 : 0x00000000\n"
      "[Fullread] LBA 05 : 0x00000000\n"
      "[Fullread] LBA 06 : 0x00000000\n"
      "[Fullread] LBA 07 : 0x00000000\n"
      "[Fullread] LBA 08 : 0x00000000\n"
      "[Fullread] LBA 09 : 0x00000000\n"
      "[Fullread] LBA 10 : 0x00000000\n"
      "[Fullread] LBA 11 : 0x00000000\n"
      "[Fullread] LBA 12 : 0x00000000\n"
      "[Fullread] LBA 13 : 0x00000000\n"
      "[Fullread] LBA 14 : 0x00000000\n"
      "[Fullread] LBA 15 : 0x00000000\n"
      "[Fullread] LBA 16 : 0x00000000\n"
      "[Fullread] LBA 17 : 0x00000000\n"
      "[Fullread] LBA 18 : 0x00000000\n"
      "[Fullread] LBA 19 : 0x00000000\n"
      "[Fullread] LBA 20 : 0x00000000\n"
      "[Fullread] LBA 21 : 0x00000000\n"
      "[Fullread] LBA 22 : 0x00000000\n"
      "[Fullread] LBA 23 : 0x00000000\n"
      "[Fullread] LBA 24 : 0x00000000\n"
      "[Fullread] LBA 25 : 0x00000000\n"
      "[Fullread] LBA 26 : 0x00000000\n"
      "[Fullread] LBA 27 : 0x00000000\n"
      "[Fullread] LBA 28 : 0x00000000\n"
      "[Fullread] LBA 29 : 0x00000000\n"
      "[Fullread] LBA 30 : 0x00000000\n"
      "[Fullread] LBA 31 : 0x00000000\n"
      "[Fullread] LBA 32 : 0x00000000\n"
      "[Fullread] LBA 33 : 0x00000000\n"
      "[Fullread] LBA 34 : 0x00000000\n"
      "[Fullread] LBA 35 : 0x00000000\n"
      "[Fullread] LBA 36 : 0x00000000\n"
      "[Fullread] LBA 37 : 0x00000000\n"
      "[Fullread] LBA 38 : 0x00000000\n"
      "[Fullread] LBA 39 : 0x00000000\n"
      "[Fullread] LBA 40 : 0x00000000\n"
      "[Fullread] LBA 41 : 0x00000000\n"
      "[Fullread] LBA 42 : 0x00000000\n"
      "[Fullread] LBA 43 : 0x00000000\n"
      "[Fullread] LBA 44 : 0x00000000\n"
      "[Fullread] LBA 45 : 0x00000000\n"
      "[Fullread] LBA 46 : 0x00000000\n"
      "[Fullread] LBA 47 : 0x00000000\n"
      "[Fullread] LBA 48 : 0x00000000\n"
      "[Fullread] LBA 49 : 0x00000000\n"
      "[Fullread] LBA 50 : 0x00000000\n"
      "[Fullread] LBA 51 : 0x00000000\n"
      "[Fullread] LBA 52 : 0x00000000\n"
      "[Fullread] LBA 53 : 0x00000000\n"
      "[Fullread] LBA 54 : 0x00000000\n"
      "[Fullread] LBA 55 : 0x00000000\n"
      "[Fullread] LBA 56 : 0x00000000\n"
      "[Fullread] LBA 57 : 0x00000000\n"
      "[Fullread] LBA 58 : 0x00000000\n"
      "[Fullread] LBA 59 : 0x00000000\n"
      "[Fullread] LBA 60 : 0x00000000\n"
      "[Fullread] LBA 61 : 0x00000000\n"
      "[Fullread] LBA 62 : 0x00000000\n"
      "[Fullread] LBA 63 : 0x00000000\n"
      "[Fullread] LBA 64 : 0x00000000\n"
      "[Fullread] LBA 65 : 0x00000000\n"
      "[Fullread] LBA 66 : 0x00000000\n"
      "[Fullread] LBA 67 : 0x00000000\n"
      "[Fullread] LBA 68 : 0x00000000\n"
      "[Fullread] LBA 69 : 0x00000000\n"
      "[Fullread] LBA 70 : 0x00000000\n"
      "[Fullread] LBA 71 : 0x00000000\n"
      "[Fullread] LBA 72 : 0x00000000\n"
      "[Fullread] LBA 73 : 0x00000000\n"
      "[Fullread] LBA 74 : 0x00000000\n"
      "[Fullread] LBA 75 : 0x00000000\n"
      "[Fullread] LBA 76 : 0x00000000\n"
      "[Fullread] LBA 77 : 0x00000000\n"
      "[Fullread] LBA 78 : 0x00000000\n"
      "[Fullread] LBA 79 : 0x00000000\n"
      "[Fullread] LBA 80 : 0x00000000\n"
      "[Fullread] LBA 81 : 0x00000000\n"
      "[Fullread] LBA 82 : 0x00000000\n"
      "[Fullread] LBA 83 : 0x00000000\n"
      "[Fullread] LBA 84 : 0x00000000\n"
      "[Fullread] LBA 85 : 0x00000000\n"
      "[Fullread] LBA 86 : 0x00000000\n"
      "[Fullread] LBA 87 : 0x00000000\n"
      "[Fullread] LBA 88 : 0x00000000\n"
      "[Fullread] LBA 89 : 0x00000000\n"
      "[Fullread] LBA 90 : 0x00000000\n"
      "[Fullread] LBA 91 : 0x00000000\n"
      "[Fullread] LBA 92 : 0x00000000\n"
      "[Fullread] LBA 93 : 0x00000000\n"
      "[Fullread] LBA 94 : 0x00000000\n"
      "[Fullread] LBA 95 : 0x00000000\n"
      "[Fullread] LBA 96 : 0x00000000\n"
      "[Fullread] LBA 97 : 0x00000000\n"
      "[Fullread] LBA 98 : 0x00000000\n"
      "[Fullread] LBA 99 : 0x00000000\n" SHELL_EXIT_OUTPUT};

  // 7
  std::vector<std::string> fullwriteAndFullread = {"fullwrite 0xAAAABBBB",
                                                   "fullread", "exit"};
  std::string fullwriteAndFullreadResult = {
      SHELL_PREFIX_OUTPUT "[Fullwrite] Done\n" SHELL_PREFIX_OUTPUT
                          "[Fullread] LBA 00 : 0xAAAABBBB\n"
                          "[Fullread] LBA 01 : 0xAAAABBBB\n"
                          "[Fullread] LBA 02 : 0xAAAABBBB\n"
                          "[Fullread] LBA 03 : 0xAAAABBBB\n"
                          "[Fullread] LBA 04 : 0xAAAABBBB\n"
                          "[Fullread] LBA 05 : 0xAAAABBBB\n"
                          "[Fullread] LBA 06 : 0xAAAABBBB\n"
                          "[Fullread] LBA 07 : 0xAAAABBBB\n"
                          "[Fullread] LBA 08 : 0xAAAABBBB\n"
                          "[Fullread] LBA 09 : 0xAAAABBBB\n"
                          "[Fullread] LBA 10 : 0xAAAABBBB\n"
                          "[Fullread] LBA 11 : 0xAAAABBBB\n"
                          "[Fullread] LBA 12 : 0xAAAABBBB\n"
                          "[Fullread] LBA 13 : 0xAAAABBBB\n"
                          "[Fullread] LBA 14 : 0xAAAABBBB\n"
                          "[Fullread] LBA 15 : 0xAAAABBBB\n"
                          "[Fullread] LBA 16 : 0xAAAABBBB\n"
                          "[Fullread] LBA 17 : 0xAAAABBBB\n"
                          "[Fullread] LBA 18 : 0xAAAABBBB\n"
                          "[Fullread] LBA 19 : 0xAAAABBBB\n"
                          "[Fullread] LBA 20 : 0xAAAABBBB\n"
                          "[Fullread] LBA 21 : 0xAAAABBBB\n"
                          "[Fullread] LBA 22 : 0xAAAABBBB\n"
                          "[Fullread] LBA 23 : 0xAAAABBBB\n"
                          "[Fullread] LBA 24 : 0xAAAABBBB\n"
                          "[Fullread] LBA 25 : 0xAAAABBBB\n"
                          "[Fullread] LBA 26 : 0xAAAABBBB\n"
                          "[Fullread] LBA 27 : 0xAAAABBBB\n"
                          "[Fullread] LBA 28 : 0xAAAABBBB\n"
                          "[Fullread] LBA 29 : 0xAAAABBBB\n"
                          "[Fullread] LBA 30 : 0xAAAABBBB\n"
                          "[Fullread] LBA 31 : 0xAAAABBBB\n"
                          "[Fullread] LBA 32 : 0xAAAABBBB\n"
                          "[Fullread] LBA 33 : 0xAAAABBBB\n"
                          "[Fullread] LBA 34 : 0xAAAABBBB\n"
                          "[Fullread] LBA 35 : 0xAAAABBBB\n"
                          "[Fullread] LBA 36 : 0xAAAABBBB\n"
                          "[Fullread] LBA 37 : 0xAAAABBBB\n"
                          "[Fullread] LBA 38 : 0xAAAABBBB\n"
                          "[Fullread] LBA 39 : 0xAAAABBBB\n"
                          "[Fullread] LBA 40 : 0xAAAABBBB\n"
                          "[Fullread] LBA 41 : 0xAAAABBBB\n"
                          "[Fullread] LBA 42 : 0xAAAABBBB\n"
                          "[Fullread] LBA 43 : 0xAAAABBBB\n"
                          "[Fullread] LBA 44 : 0xAAAABBBB\n"
                          "[Fullread] LBA 45 : 0xAAAABBBB\n"
                          "[Fullread] LBA 46 : 0xAAAABBBB\n"
                          "[Fullread] LBA 47 : 0xAAAABBBB\n"
                          "[Fullread] LBA 48 : 0xAAAABBBB\n"
                          "[Fullread] LBA 49 : 0xAAAABBBB\n"
                          "[Fullread] LBA 50 : 0xAAAABBBB\n"
                          "[Fullread] LBA 51 : 0xAAAABBBB\n"
                          "[Fullread] LBA 52 : 0xAAAABBBB\n"
                          "[Fullread] LBA 53 : 0xAAAABBBB\n"
                          "[Fullread] LBA 54 : 0xAAAABBBB\n"
                          "[Fullread] LBA 55 : 0xAAAABBBB\n"
                          "[Fullread] LBA 56 : 0xAAAABBBB\n"
                          "[Fullread] LBA 57 : 0xAAAABBBB\n"
                          "[Fullread] LBA 58 : 0xAAAABBBB\n"
                          "[Fullread] LBA 59 : 0xAAAABBBB\n"
                          "[Fullread] LBA 60 : 0xAAAABBBB\n"
                          "[Fullread] LBA 61 : 0xAAAABBBB\n"
                          "[Fullread] LBA 62 : 0xAAAABBBB\n"
                          "[Fullread] LBA 63 : 0xAAAABBBB\n"
                          "[Fullread] LBA 64 : 0xAAAABBBB\n"
                          "[Fullread] LBA 65 : 0xAAAABBBB\n"
                          "[Fullread] LBA 66 : 0xAAAABBBB\n"
                          "[Fullread] LBA 67 : 0xAAAABBBB\n"
                          "[Fullread] LBA 68 : 0xAAAABBBB\n"
                          "[Fullread] LBA 69 : 0xAAAABBBB\n"
                          "[Fullread] LBA 70 : 0xAAAABBBB\n"
                          "[Fullread] LBA 71 : 0xAAAABBBB\n"
                          "[Fullread] LBA 72 : 0xAAAABBBB\n"
                          "[Fullread] LBA 73 : 0xAAAABBBB\n"
                          "[Fullread] LBA 74 : 0xAAAABBBB\n"
                          "[Fullread] LBA 75 : 0xAAAABBBB\n"
                          "[Fullread] LBA 76 : 0xAAAABBBB\n"
                          "[Fullread] LBA 77 : 0xAAAABBBB\n"
                          "[Fullread] LBA 78 : 0xAAAABBBB\n"
                          "[Fullread] LBA 79 : 0xAAAABBBB\n"
                          "[Fullread] LBA 80 : 0xAAAABBBB\n"
                          "[Fullread] LBA 81 : 0xAAAABBBB\n"
                          "[Fullread] LBA 82 : 0xAAAABBBB\n"
                          "[Fullread] LBA 83 : 0xAAAABBBB\n"
                          "[Fullread] LBA 84 : 0xAAAABBBB\n"
                          "[Fullread] LBA 85 : 0xAAAABBBB\n"
                          "[Fullread] LBA 86 : 0xAAAABBBB\n"
                          "[Fullread] LBA 87 : 0xAAAABBBB\n"
                          "[Fullread] LBA 88 : 0xAAAABBBB\n"
                          "[Fullread] LBA 89 : 0xAAAABBBB\n"
                          "[Fullread] LBA 90 : 0xAAAABBBB\n"
                          "[Fullread] LBA 91 : 0xAAAABBBB\n"
                          "[Fullread] LBA 92 : 0xAAAABBBB\n"
                          "[Fullread] LBA 93 : 0xAAAABBBB\n"
                          "[Fullread] LBA 94 : 0xAAAABBBB\n"
                          "[Fullread] LBA 95 : 0xAAAABBBB\n"
                          "[Fullread] LBA 96 : 0xAAAABBBB\n"
                          "[Fullread] LBA 97 : 0xAAAABBBB\n"
                          "[Fullread] LBA 98 : 0xAAAABBBB\n"
                          "[Fullread] LBA 99 : 0xAAAABBBB\n" SHELL_EXIT_OUTPUT};

  // 8
  std::vector<std::string> invalidCommand = {"strange_commands", "exit"};
  std::string invalidCommandResult = {SHELL_PREFIX_OUTPUT
                                      "INVALID COMMAND\n" SHELL_EXIT_OUTPUT};

  // 9
  std::vector<std::string> ts1Command = {"1_FullWriteAndReadCompare", "exit"};
  std::vector<std::string> ts1CommandShort = {"1_", "exit"};
  std::string ts1CommandResult = {
      SHELL_PREFIX_OUTPUT SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000000\n"
      "[Read] LBA 01 : 0x00000000\n"
      "[Read] LBA 02 : 0x00000000\n"
      "[Read] LBA 03 : 0x00000000\n"
      "[Read] LBA 04 : 0x00000000\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 05 : 0x00000005\n"
      "[Read] LBA 06 : 0x00000005\n"
      "[Read] LBA 07 : 0x00000005\n"
      "[Read] LBA 08 : 0x00000005\n"
      "[Read] LBA 09 : 0x00000005\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 10 : 0x0000000A\n"
      "[Read] LBA 11 : 0x0000000A\n"
      "[Read] LBA 12 : 0x0000000A\n"
      "[Read] LBA 13 : 0x0000000A\n"
      "[Read] LBA 14 : 0x0000000A\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 15 : 0x0000000F\n"
      "[Read] LBA 16 : 0x0000000F\n"
      "[Read] LBA 17 : 0x0000000F\n"
      "[Read] LBA 18 : 0x0000000F\n"
      "[Read] LBA 19 : 0x0000000F\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 20 : 0x00000014\n"
      "[Read] LBA 21 : 0x00000014\n"
      "[Read] LBA 22 : 0x00000014\n"
      "[Read] LBA 23 : 0x00000014\n"
      "[Read] LBA 24 : 0x00000014\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 25 : 0x00000019\n"
      "[Read] LBA 26 : 0x00000019\n"
      "[Read] LBA 27 : 0x00000019\n"
      "[Read] LBA 28 : 0x00000019\n"
      "[Read] LBA 29 : 0x00000019\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 30 : 0x0000001E\n"
      "[Read] LBA 31 : 0x0000001E\n"
      "[Read] LBA 32 : 0x0000001E\n"
      "[Read] LBA 33 : 0x0000001E\n"
      "[Read] LBA 34 : 0x0000001E\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 35 : 0x00000023\n"
      "[Read] LBA 36 : 0x00000023\n"
      "[Read] LBA 37 : 0x00000023\n"
      "[Read] LBA 38 : 0x00000023\n"
      "[Read] LBA 39 : 0x00000023\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 40 : 0x00000028\n"
      "[Read] LBA 41 : 0x00000028\n"
      "[Read] LBA 42 : 0x00000028\n"
      "[Read] LBA 43 : 0x00000028\n"
      "[Read] LBA 44 : 0x00000028\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 45 : 0x0000002D\n"
      "[Read] LBA 46 : 0x0000002D\n"
      "[Read] LBA 47 : 0x0000002D\n"
      "[Read] LBA 48 : 0x0000002D\n"
      "[Read] LBA 49 : 0x0000002D\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 50 : 0x00000032\n"
      "[Read] LBA 51 : 0x00000032\n"
      "[Read] LBA 52 : 0x00000032\n"
      "[Read] LBA 53 : 0x00000032\n"
      "[Read] LBA 54 : 0x00000032\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 55 : 0x00000037\n"
      "[Read] LBA 56 : 0x00000037\n"
      "[Read] LBA 57 : 0x00000037\n"
      "[Read] LBA 58 : 0x00000037\n"
      "[Read] LBA 59 : 0x00000037\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 60 : 0x0000003C\n"
      "[Read] LBA 61 : 0x0000003C\n"
      "[Read] LBA 62 : 0x0000003C\n"
      "[Read] LBA 63 : 0x0000003C\n"
      "[Read] LBA 64 : 0x0000003C\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 65 : 0x00000041\n"
      "[Read] LBA 66 : 0x00000041\n"
      "[Read] LBA 67 : 0x00000041\n"
      "[Read] LBA 68 : 0x00000041\n"
      "[Read] LBA 69 : 0x00000041\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 70 : 0x00000046\n"
      "[Read] LBA 71 : 0x00000046\n"
      "[Read] LBA 72 : 0x00000046\n"
      "[Read] LBA 73 : 0x00000046\n"
      "[Read] LBA 74 : 0x00000046\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 75 : 0x0000004B\n"
      "[Read] LBA 76 : 0x0000004B\n"
      "[Read] LBA 77 : 0x0000004B\n"
      "[Read] LBA 78 : 0x0000004B\n"
      "[Read] LBA 79 : 0x0000004B\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 80 : 0x00000050\n"
      "[Read] LBA 81 : 0x00000050\n"
      "[Read] LBA 82 : 0x00000050\n"
      "[Read] LBA 83 : 0x00000050\n"
      "[Read] LBA 84 : 0x00000050\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 85 : 0x00000055\n"
      "[Read] LBA 86 : 0x00000055\n"
      "[Read] LBA 87 : 0x00000055\n"
      "[Read] LBA 88 : 0x00000055\n"
      "[Read] LBA 89 : 0x00000055\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 90 : 0x0000005A\n"
      "[Read] LBA 91 : 0x0000005A\n"
      "[Read] LBA 92 : 0x0000005A\n"
      "[Read] LBA 93 : 0x0000005A\n"
      "[Read] LBA 94 : 0x0000005A\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 95 : 0x0000005F\n"
      "[Read] LBA 96 : 0x0000005F\n"
      "[Read] LBA 97 : 0x0000005F\n"
      "[Read] LBA 98 : 0x0000005F\n"
      "[Read] LBA 99 : 0x0000005F\n" SHELL_EXIT_OUTPUT};

  // 10
  std::vector<std::string> ts2Command = {"2_PartialLBAWrite", "exit"};
  std::vector<std::string> ts2CommandShort = {"2_", "exit"};
  std::string ts2CommandResult = {
      SHELL_PREFIX_OUTPUT SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000000\n"
      "[Read] LBA 01 : 0x00000000\n"
      "[Read] LBA 02 : 0x00000000\n"
      "[Read] LBA 03 : 0x00000000\n"
      "[Read] LBA 04 : 0x00000000\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000001\n"
      "[Read] LBA 01 : 0x00000001\n"
      "[Read] LBA 02 : 0x00000001\n"
      "[Read] LBA 03 : 0x00000001\n"
      "[Read] LBA 04 : 0x00000001\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000002\n"
      "[Read] LBA 01 : 0x00000002\n"
      "[Read] LBA 02 : 0x00000002\n"
      "[Read] LBA 03 : 0x00000002\n"
      "[Read] LBA 04 : 0x00000002\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000003\n"
      "[Read] LBA 01 : 0x00000003\n"
      "[Read] LBA 02 : 0x00000003\n"
      "[Read] LBA 03 : 0x00000003\n"
      "[Read] LBA 04 : 0x00000003\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000004\n"
      "[Read] LBA 01 : 0x00000004\n"
      "[Read] LBA 02 : 0x00000004\n"
      "[Read] LBA 03 : 0x00000004\n"
      "[Read] LBA 04 : 0x00000004\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000005\n"
      "[Read] LBA 01 : 0x00000005\n"
      "[Read] LBA 02 : 0x00000005\n"
      "[Read] LBA 03 : 0x00000005\n"
      "[Read] LBA 04 : 0x00000005\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000006\n"
      "[Read] LBA 01 : 0x00000006\n"
      "[Read] LBA 02 : 0x00000006\n"
      "[Read] LBA 03 : 0x00000006\n"
      "[Read] LBA 04 : 0x00000006\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000007\n"
      "[Read] LBA 01 : 0x00000007\n"
      "[Read] LBA 02 : 0x00000007\n"
      "[Read] LBA 03 : 0x00000007\n"
      "[Read] LBA 04 : 0x00000007\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000008\n"
      "[Read] LBA 01 : 0x00000008\n"
      "[Read] LBA 02 : 0x00000008\n"
      "[Read] LBA 03 : 0x00000008\n"
      "[Read] LBA 04 : 0x00000008\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000009\n"
      "[Read] LBA 01 : 0x00000009\n"
      "[Read] LBA 02 : 0x00000009\n"
      "[Read] LBA 03 : 0x00000009\n"
      "[Read] LBA 04 : 0x00000009\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x0000000A\n"
      "[Read] LBA 01 : 0x0000000A\n"
      "[Read] LBA 02 : 0x0000000A\n"
      "[Read] LBA 03 : 0x0000000A\n"
      "[Read] LBA 04 : 0x0000000A\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x0000000B\n"
      "[Read] LBA 01 : 0x0000000B\n"
      "[Read] LBA 02 : 0x0000000B\n"
      "[Read] LBA 03 : 0x0000000B\n"
      "[Read] LBA 04 : 0x0000000B\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x0000000C\n"
      "[Read] LBA 01 : 0x0000000C\n"
      "[Read] LBA 02 : 0x0000000C\n"
      "[Read] LBA 03 : 0x0000000C\n"
      "[Read] LBA 04 : 0x0000000C\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x0000000D\n"
      "[Read] LBA 01 : 0x0000000D\n"
      "[Read] LBA 02 : 0x0000000D\n"
      "[Read] LBA 03 : 0x0000000D\n"
      "[Read] LBA 04 : 0x0000000D\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x0000000E\n"
      "[Read] LBA 01 : 0x0000000E\n"
      "[Read] LBA 02 : 0x0000000E\n"
      "[Read] LBA 03 : 0x0000000E\n"
      "[Read] LBA 04 : 0x0000000E\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x0000000F\n"
      "[Read] LBA 01 : 0x0000000F\n"
      "[Read] LBA 02 : 0x0000000F\n"
      "[Read] LBA 03 : 0x0000000F\n"
      "[Read] LBA 04 : 0x0000000F\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000010\n"
      "[Read] LBA 01 : 0x00000010\n"
      "[Read] LBA 02 : 0x00000010\n"
      "[Read] LBA 03 : 0x00000010\n"
      "[Read] LBA 04 : 0x00000010\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000011\n"
      "[Read] LBA 01 : 0x00000011\n"
      "[Read] LBA 02 : 0x00000011\n"
      "[Read] LBA 03 : 0x00000011\n"
      "[Read] LBA 04 : 0x00000011\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000012\n"
      "[Read] LBA 01 : 0x00000012\n"
      "[Read] LBA 02 : 0x00000012\n"
      "[Read] LBA 03 : 0x00000012\n"
      "[Read] LBA 04 : 0x00000012\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000013\n"
      "[Read] LBA 01 : 0x00000013\n"
      "[Read] LBA 02 : 0x00000013\n"
      "[Read] LBA 03 : 0x00000013\n"
      "[Read] LBA 04 : 0x00000013\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000014\n"
      "[Read] LBA 01 : 0x00000014\n"
      "[Read] LBA 02 : 0x00000014\n"
      "[Read] LBA 03 : 0x00000014\n"
      "[Read] LBA 04 : 0x00000014\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000015\n"
      "[Read] LBA 01 : 0x00000015\n"
      "[Read] LBA 02 : 0x00000015\n"
      "[Read] LBA 03 : 0x00000015\n"
      "[Read] LBA 04 : 0x00000015\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000016\n"
      "[Read] LBA 01 : 0x00000016\n"
      "[Read] LBA 02 : 0x00000016\n"
      "[Read] LBA 03 : 0x00000016\n"
      "[Read] LBA 04 : 0x00000016\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000017\n"
      "[Read] LBA 01 : 0x00000017\n"
      "[Read] LBA 02 : 0x00000017\n"
      "[Read] LBA 03 : 0x00000017\n"
      "[Read] LBA 04 : 0x00000017\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000018\n"
      "[Read] LBA 01 : 0x00000018\n"
      "[Read] LBA 02 : 0x00000018\n"
      "[Read] LBA 03 : 0x00000018\n"
      "[Read] LBA 04 : 0x00000018\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x00000019\n"
      "[Read] LBA 01 : 0x00000019\n"
      "[Read] LBA 02 : 0x00000019\n"
      "[Read] LBA 03 : 0x00000019\n"
      "[Read] LBA 04 : 0x00000019\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x0000001A\n"
      "[Read] LBA 01 : 0x0000001A\n"
      "[Read] LBA 02 : 0x0000001A\n"
      "[Read] LBA 03 : 0x0000001A\n"
      "[Read] LBA 04 : 0x0000001A\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x0000001B\n"
      "[Read] LBA 01 : 0x0000001B\n"
      "[Read] LBA 02 : 0x0000001B\n"
      "[Read] LBA 03 : 0x0000001B\n"
      "[Read] LBA 04 : 0x0000001B\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x0000001C\n"
      "[Read] LBA 01 : 0x0000001C\n"
      "[Read] LBA 02 : 0x0000001C\n"
      "[Read] LBA 03 : 0x0000001C\n"
      "[Read] LBA 04 : 0x0000001C\n" SHELL_WRITE_DONE_OUTPUT
          SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
              SHELL_WRITE_DONE_OUTPUT SHELL_WRITE_DONE_OUTPUT
      "[Read] LBA 00 : 0x0000001D\n"
      "[Read] LBA 01 : 0x0000001D\n"
      "[Read] LBA 02 : 0x0000001D\n"
      "[Read] LBA 03 : 0x0000001D\n"
      "[Read] LBA 04 : 0x0000001D\n" SHELL_EXIT_OUTPUT};

  // 11
  std::vector<std::string> ts3Command = {"3_WriteReadAging", "exit"};
  std::vector<std::string> ts3CommandShort = {"3_", "exit"};
  std::string ts3CommandResult = {SHELL_PREFIX_OUTPUT SHELL_EXIT_OUTPUT};
};

// 1
TEST_F(TestShellFixture, mockStartAndExit) {
  SendCommandToMock(startAndExit, startAndExitResult);
}

TEST_F(TestShellFixture, realStartAndExit) {
  SendCommandToReal(startAndExit, startAndExitResult);
}

// 2
TEST_F(TestShellFixture, mockWrite) { SendCommandToMock(write, writeResult); }

TEST_F(TestShellFixture, realWrite) { SendCommandToReal(write, writeResult); }

// 3
TEST_F(TestShellFixture, mockRead) { SendCommandToMock(read, readResult); }

TEST_F(TestShellFixture, realRead) { SendCommandToReal(read, readResult); }

// 4
TEST_F(TestShellFixture, mockWriteAndRead) {
  SendCommandToMock(writeAndRead, writeAndReadResult);
}

TEST_F(TestShellFixture, realWriteAndRead) {
  SendCommandToReal(writeAndRead, writeAndReadResult);
}

// 5
TEST_F(TestShellFixture, mockFullwrite) {
  SendCommandToMock(fullwrite, fullwriteResult);
}

TEST_F(TestShellFixture, realFullwrite) {
  SendCommandToReal(fullwrite, fullwriteResult);
}

// 6
TEST_F(TestShellFixture, mockFullread) {
  SendCommandToMock(fullread, fullreadResult);
}

TEST_F(TestShellFixture, realFullread) {
  SendCommandToReal(fullread, fullreadResult);
}

// 7
TEST_F(TestShellFixture, mockFullwriteAndFullread) {
  SendCommandToMock(fullwriteAndFullread, fullwriteAndFullreadResult);
}

TEST_F(TestShellFixture, realFullwriteAndFullread) {
  SendCommandToReal(fullwriteAndFullread, fullwriteAndFullreadResult);
}

// 8
TEST_F(TestShellFixture, mockInvalidCommand) {
  SendCommandToMock(invalidCommand, invalidCommandResult);
}

TEST_F(TestShellFixture, realInvalidCommand) {
  SendCommandToReal(invalidCommand, invalidCommandResult);
}

// 9
TEST_F(TestShellFixture, mockTs1Command) {
  SendCommandToMock(ts1Command, ts1CommandResult);
  SendCommandToMock(ts1CommandShort, ts1CommandResult);
}

TEST_F(TestShellFixture, realTs1Command) {
  SendCommandToReal(ts1Command, ts1CommandResult);
  SendCommandToReal(ts1CommandShort, ts1CommandResult);
}

// 10
TEST_F(TestShellFixture, mockTs2Command) {
  SendCommandToMock(ts2Command, ts2CommandResult);
  SendCommandToMock(ts2CommandShort, ts2CommandResult);
}

TEST_F(TestShellFixture, realTs2Command) {
  SendCommandToReal(ts2Command, ts2CommandResult);
  SendCommandToReal(ts2CommandShort, ts2CommandResult);
}

// 11
TEST_F(TestShellFixture, mockTs3Command) {
  SendCommandToMock(ts3Command, ts3CommandResult);
  SendCommandToMock(ts3CommandShort, ts3CommandResult);
}

// We need to consider a method to check the results using a random number test.
TEST_F(TestShellFixture, DISABLED_realTs3Command) {
  SendCommandToReal(ts3Command, ts3CommandResult);
  SendCommandToReal(ts3CommandShort, ts3CommandResult);
}