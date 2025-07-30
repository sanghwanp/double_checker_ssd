#include <string>

#include "../Shell/Parser.h"
#include "gmock/gmock.h"

using std::string;

class FixtureParser : public ::testing::Test {
 public:
  Parser parser;
  string testStr;
  CommandStruct cmd;
  void SetUp() override {
  }
  void SetupInputString(const string& input) {
    testStr = input;
  }
};

TEST_F(FixtureParser, empty_fail) {
  SetupInputString("");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd.commandName, "error");
}

TEST_F(FixtureParser, write_command_struct_over_args) {
  SetupInputString("write 123 456 extra");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd.commandName, "error");
}

TEST_F(FixtureParser, write_command_struct_first_number_check) {
  SetupInputString("write www 456");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd.commandName, "error");
}

TEST_F(FixtureParser, write_command_struct_second_number_check) {
  SetupInputString("write 123 eee");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd.commandName, "error");
}

TEST(gTestParserTS, write_command_parse_success) {}
TEST(gTestParserTS, read_command_struct_first_string_check) {}
TEST(gTestParserTS, read_command_struct_second_number_check) {}
TEST(gTestParserTS, read_command_parse_success) {}

TEST(gTestParserTS, read_command_parse) {}
TEST(gTestParserTS, exit_command_parse) {}
TEST(gTestParserTS, help_command_parse) {}
TEST(gTestParserTS, fullwrite_command_parse) {}
TEST(gTestParserTS, fullwrite_command_struct_first_number_decimal_check) {}
TEST(gTestParserTS, fullwrite_command_struct_first_number_hex_check) {}
TEST(gTestParserTS, fullread_command_parse) {}
