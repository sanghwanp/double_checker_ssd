#pragma once
// #include "Parser.h"
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "IParam.h"

using std::string;
using std::vector;

struct CommandParamSpec {
  int argCount;
  TestShellCMD eCmd;
  std::function<IParam*(const std::vector<std::string>&)> paramObj;
  std::function<bool(const std::vector<std::string>&)> validator;
};

struct ScriptSpec {
  int argCount;
  TestShellCMD eCmd;
  std::function<IParam*(const std::vector<std::string>&)> paramObj;
  std::function<bool(const std::vector<std::string>&)> validator;
};



class Parser {
 public:
  std::vector<std::string> SplitArgs(const std::string& input);
  IParam* Parse(const std::string& input);
  bool IsValidCommandStructure(const vector<std::string>& tokens);
  bool IsNumber(const std::string& str);
  bool IsDec(const std::string& str);
  bool IsHex(const std::string& str);
  IParam* GenCommandParam(std::vector<std::string> tokens);
  bool IsValidScriptCommandStructure(const vector<std::string>& tokens);

 private:
  IParam* GetInvalidCommand() { return new IParam(TestShellCMD::eInvalidCmd); }
  string ExtractScriptNumberIfValidFormat(const std::string& str);
  IParam* Parser::GenScriptParam(std::vector<std::string>& tokens);


  const std::unordered_map<std::string, CommandParamSpec> commandParamSpecs = {
      {"write",
       {3, TestShellCMD::eWriteCmd,
        [&](const std::vector<std::string>& tokens) {
          return new WriteParam(TestShellCMD::eWriteCmd, tokens[1], tokens[2]);},
        [&](const std::vector<std::string>& tokens) {
          return IsNumber(tokens[1]) && IsNumber(tokens[2]);
        }}},
      {"read",
       {2, TestShellCMD::eReadCmd,
        [&](const std::vector<std::string>& tokens) {
          return new ReadParam(TestShellCMD::eReadCmd, tokens[1]);},
        [&](const std::vector<std::string>& tokens) {
          return IsNumber(tokens[1]);
        }}},
      {"fullwrite",
       {2, TestShellCMD::eFullwrite,
        [&](const std::vector<std::string>& tokens) {
          return new FullWriteParam(TestShellCMD::eFullwrite, tokens[1]);},
        [&](const std::vector<std::string>& tokens) {
          return IsNumber(tokens[1]);
        }}},
      {"exit",
       {1, TestShellCMD::eExitCmd, 
            [](const std::vector<std::string>& tokens) {
          return new IParam(TestShellCMD::eExitCmd);},
        [](const std::vector<std::string>&) { return true; }}},
      {"help",
       {1, TestShellCMD::eHelpCmd,
        [](const std::vector<std::string>& tokens) {
          return new IParam(TestShellCMD::eHelpCmd);
        },
        [](const std::vector<std::string>&) { return true; }}},
      {"fullread",
       {1, TestShellCMD::eFullread,
        [](const std::vector<std::string>& tokens) {
          return new IParam(TestShellCMD::eFullread);
        },
        [](const std::vector<std::string>&) { return true; }}},
      {"flush",
       {1, TestShellCMD::eFlushCmd,
        [](const std::vector<std::string>& tokens) {
          return new IParam(TestShellCMD::eFlushCmd);
        },
        [](const std::vector<std::string>&) { return true; }}},
      {"erase",
       {3, TestShellCMD::eEraseCmd,
        [&](const std::vector<std::string>& tokens) {
          return new EraseParam(TestShellCMD::eEraseCmd, tokens[1], tokens[2]);
        },
        [&](const std::vector<std::string>& tokens) {
          return IsNumber(tokens[1]) && IsNumber(tokens[2]);
        }}},
      {"erase_range",
       {3, TestShellCMD::eEraseRangeCmd,
        [&](const std::vector<std::string>& tokens) {
          return new EraseRangeParam(TestShellCMD::eEraseRangeCmd, tokens[1], tokens[2]);
        },
        [&](const std::vector<std::string>& tokens) {
          return IsNumber(tokens[1]) && IsNumber(tokens[2]);
        }}},
      {"script",
       {1, TestShellCMD::eScriptCmd,
        [&](const std::vector<std::string>& tokens) {
          return new ScriptParam(TestShellCMD::eScriptCmd,
                                 ExtractScriptNumberIfValidFormat(tokens[0]));
        },
        [](const std::vector<std::string>&) { return true; }}}};
};
