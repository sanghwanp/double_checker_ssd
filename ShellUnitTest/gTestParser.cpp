#include <string>
#include "../Shell/Parser.h"
#include "gmock/gmock.h"

using std::string;
using ::testing::Test;

class FixtureParser : public ::Test {
 public:
  Parser parser;
  string testStr;
  IParam* cmd;
  void SetUp() override {}
  void SetupInputString(const string& input) { testStr = input; }
};

TEST_F(FixtureParser, empty_fail) {
  SetupInputString("");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eInvalidCmd);
}

TEST_F(FixtureParser, write_command_struct_over_args) {
  SetupInputString("write 123 456 extra");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eInvalidCmd);
}

TEST_F(FixtureParser, write_command_struct_first_number_check) {
  SetupInputString("write www 456");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eInvalidCmd);
}

TEST_F(FixtureParser, write_command_struct_second_number_check) {
  SetupInputString("write 123 eee");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eInvalidCmd);
}

TEST_F(FixtureParser, write_command_parse_success) {
  SetupInputString("write 33 0x12341234");
  cmd = parser.Parse(testStr);
  WriteParam* writeCmd = dynamic_cast<WriteParam*>(cmd);

  EXPECT_EQ(writeCmd->eCmd, TestShellCMD::eWriteCmd);
  EXPECT_EQ(writeCmd->lba, "33");
  EXPECT_EQ(writeCmd->data, "0x12341234");
}

TEST_F(FixtureParser, read_command_struct_first_string_check) {
  SetupInputString("read abc");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eInvalidCmd);
}
TEST_F(FixtureParser, read_command_struct_over_args_check) {
  SetupInputString("read 123 eee");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eInvalidCmd);

  SetupInputString("read 123 eee 123");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eInvalidCmd);
}

TEST_F(FixtureParser, read_command_parse_success) {
  SetupInputString("read 123");
  cmd = parser.Parse(testStr);
  ReadParam* readCmd = dynamic_cast<ReadParam*>(cmd);

  EXPECT_EQ(readCmd->eCmd, eReadCmd);
  EXPECT_EQ(readCmd->lba, "123");
}

TEST_F(FixtureParser, exit_command_parse) {
  SetupInputString("exit");
  cmd = parser.Parse(testStr);

  EXPECT_EQ(cmd->eCmd, eExitCmd);
}
TEST_F(FixtureParser, help_command_parse) {
  SetupInputString("help");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eHelpCmd);
}

TEST_F(FixtureParser, fullwrite_command_parse) {
  SetupInputString("fullwrite 0x12341234");
  cmd = parser.Parse(testStr);
  FullWriteParam* fwCmd = dynamic_cast<FullWriteParam*>(cmd);

  EXPECT_EQ(fwCmd->eCmd, eFullwrite);
  EXPECT_EQ(fwCmd->data, "0x12341234");
}

TEST_F(FixtureParser, fullwrite_command_struct_first_number_decimal_check) {
  SetupInputString("fullwrite aaw");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eInvalidCmd);
}

TEST_F(FixtureParser, fullwrite_command_struct_over_args) {
  SetupInputString("fullwrite 0x12341234 0");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eInvalidCmd);
}

TEST_F(FixtureParser, fullwrite_command_struct_first_number_hex_check) {
  SetupInputString("fullwrite 0x12341234 0x1234");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eInvalidCmd);
}

TEST_F(FixtureParser, fullread_command_parse) {
  SetupInputString("fullread");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eFullread);
}


TEST_F(FixtureParser, erase_command_struct_over_args) {
  SetupInputString("erase 10 10 10");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eInvalidCmd);
}
TEST_F(FixtureParser, erase_command_struct_first_number_check) {
  SetupInputString("erase www 10");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eInvalidCmd);
}
TEST_F(FixtureParser, erase_command_struct_second_number_check) {
  SetupInputString("erase 10 www");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eInvalidCmd);
}
TEST_F(FixtureParser, erase_command_parse_success) {
  SetupInputString("erase 10 10");
  cmd = parser.Parse(testStr);
  EraseParam* eraseCmd = dynamic_cast<EraseParam*>(cmd);

  EXPECT_EQ(eraseCmd->eCmd, TestShellCMD::eEraseCmd);
  EXPECT_EQ(eraseCmd->lba, "10");
  EXPECT_EQ(eraseCmd->size, "10");
}

TEST_F(FixtureParser, script_command_parse) {
  SetupInputString("1_");
  cmd = parser.Parse(testStr);
  ScriptParam* scriptCmd = dynamic_cast<ScriptParam*>(cmd);

  EXPECT_EQ(scriptCmd->eCmd, eScriptCmd);
  EXPECT_EQ(scriptCmd->scriptNumber, "1");
  EXPECT_EQ(scriptCmd->nScriptNumber, 1);
}

TEST_F(FixtureParser, script_command_parse_largeNumber) {
  SetupInputString("123123_");
  cmd = parser.Parse(testStr);
  ScriptParam* scriptCmd = dynamic_cast<ScriptParam*>(cmd);

  EXPECT_EQ(scriptCmd->eCmd, eScriptCmd);
  EXPECT_EQ(scriptCmd->scriptNumber, "123123");
  EXPECT_EQ(scriptCmd->nScriptNumber, 123123);
}

TEST_F(FixtureParser, script_command_parse_full_name1) {
  SetupInputString("1_FullWriteAndReadCompare");
  cmd = parser.Parse(testStr);
  ScriptParam* scriptCmd = dynamic_cast<ScriptParam*>(cmd);

  EXPECT_EQ(scriptCmd->eCmd, eScriptCmd);
  EXPECT_EQ(scriptCmd->scriptNumber, "1");
  EXPECT_EQ(scriptCmd->nScriptNumber, 1);
}

TEST_F(FixtureParser, script_command_parse_full_name2) {
  SetupInputString("2_PartialLBAWrite");
  cmd = parser.Parse(testStr);
  ScriptParam* scriptCmd = dynamic_cast<ScriptParam*>(cmd);

  EXPECT_EQ(scriptCmd->eCmd, eScriptCmd);
  EXPECT_EQ(scriptCmd->scriptNumber, "2");
  EXPECT_EQ(scriptCmd->nScriptNumber, 2);
}

TEST_F(FixtureParser, script_command_parse_invalid_name) {
  SetupInputString("_Partial");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eInvalidCmd);
}
TEST_F(FixtureParser, flush_command_fail_over_args) {
  SetupInputString("flush 1123");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eInvalidCmd);
}
TEST_F(FixtureParser, flush_command_success) {
  SetupInputString("flush");
  cmd = parser.Parse(testStr);
  EXPECT_EQ(cmd->eCmd, eFlushCmd);
}
