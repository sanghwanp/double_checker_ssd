#pragma once
#include <functional>
#include <unordered_map>
#include <vector>

#include "IParam.h"
#include "Types.h"

using std::vector;

struct CommandParamSpec {
  int argCount;
  CMD_TYPE eCmd;
  std::function<IParam*(const vector<string>&)> paramObj;
  std::function<bool(const vector<string>&)> validator;
};

class Parser {
 public:
  IParam* Parse(const vector<string>& tokens);

 private:
  bool IsValidCommandStructure(const vector<string>& tokens);
  IParam* GetInvalidCommand() { return new IParam(CMD_TYPE::eInvalidCmd); }
  IParam* GenCommandParam(const vector<string>& tokens);

  const std::unordered_map<string, CommandParamSpec> commandParamSpecs = {
      {"W",
       {3, CMD_TYPE::eWriteCmd,
        [](const vector<string>& tokens) {
          return new WriteParam(CMD_TYPE::eWriteCmd, LBA::Parse(tokens[1]),
                                DATA::Parse(tokens[2]));
        },
        [](const vector<string>& tokens) {
          return LBA::IsValid(tokens[1]) && DATA::IsValid(tokens[2]);
        }}},
      {"R",
       {2, CMD_TYPE::eReadCmd,
        [](const vector<string>& tokens) {
          return new ReadParam(CMD_TYPE::eReadCmd, LBA::Parse(tokens[1]));
        },
        [](const vector<string>& tokens) { return LBA::IsValid(tokens[1]); }}},
      {"E",
       {3, CMD_TYPE::eEraseCmd,
        [](const vector<string>& tokens) {
          return new EraseParam(CMD_TYPE::eEraseCmd, LBA::Parse(tokens[1]),
                                SIZE_E::Parse(tokens[2]));
        },
        [](const vector<string>& tokens) {
          return LBA::IsValid(tokens[1]) &&
                 SIZE_E::IsValid(tokens[1], tokens[2]);
        }}},
      {"F",
       {1, CMD_TYPE::eFlushCmd,
        [](const vector<string>& tokens) {
          return new FlushParam(CMD_TYPE::eFlushCmd);
        },
        [](const vector<string>& tokens) {
          return true;
        }}},
  };
};
