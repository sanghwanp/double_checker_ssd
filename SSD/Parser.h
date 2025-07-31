#pragma once

#include "IParam.h"
#include <functional>
#include <unordered_map>
#include <vector>

using std::vector;

struct CommandParamSpec {
  int argCount;
  SSD_CMD eCmd;
  std::function<IParam*(const vector<string>&)> paramObj;
  std::function<bool(const vector<string>&)> validator;
};

class Parser {
 public:
  IParam* Parse(vector<string> tokens);
  bool IsValidCommandStructure(const vector<string>& tokens);
  bool IsNumber(const string& str);
  bool IsDec(const string& str);
  bool IsHex(const string& str);
  IParam* GenCommandParam(vector<string> tokens);

 private:
  IParam* GetInvalidCommand() { return new IParam(SSD_CMD::eInvalidCmd); }

  const std::unordered_map<string, CommandParamSpec> commandParamSpecs = {
      {"write",
       {3, SSD_CMD::eWriteCmd,
        [&](const vector<string>& tokens) {
          return new WriteParam(SSD_CMD::eWriteCmd, tokens[1], tokens[2]);
        },
        [&](const vector<string>& tokens) {
          return IsNumber(tokens[1]) && IsNumber(tokens[2]);
        }}},
      {"read",
       {2, SSD_CMD::eReadCmd,
        [&](const vector<string>& tokens) {
          return new ReadParam(SSD_CMD::eReadCmd, tokens[1]);
        },
        [&](const vector<string>& tokens) { return IsNumber(tokens[1]); }}},
  };
};