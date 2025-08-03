#pragma once
#include <string>
using std::string;
enum TestShellCMD {
  eWriteCmd,
  eReadCmd,
  eHelpCmd,
  eExitCmd,
  eFullwriteCmd,
  eFullreadCmd,
  eFlushCmd,
  eEraseCmd,
  eEraseRangeCmd,
  eScriptCmd,
  eInvalidCmd,
  eDoubleChecker
};

class IParam {
 public:
  IParam(TestShellCMD cmd) : eCmd(cmd) {}
  virtual ~IParam() {} 

  TestShellCMD eCmd;
};

class WriteParam : public IParam {
 public:
  WriteParam(TestShellCMD cmd, string lba, string data)
      : IParam(cmd), lba(lba), data(data) {}
  string lba;
  string data;
};

class ReadParam : public IParam {
 public:
  ReadParam(TestShellCMD cmd, string lba) : IParam(cmd), lba(lba) {}
  string lba;
};

class FullWriteParam : public IParam {
 public:
  FullWriteParam(TestShellCMD cmd, string data) : IParam(cmd), data(data) {}
  string data;
};

class EraseParam : public IParam {
 public:
  EraseParam(TestShellCMD cmd, string lba, string size) : IParam(cmd), lba(lba), size(size) {}
  string lba;
  string size;
};

class EraseRangeParam : public IParam {
 public:
  EraseRangeParam(TestShellCMD cmd, string lbaStart, string lbaEnd)
      : IParam(cmd), lbaStart(lbaStart), lbaEnd(lbaEnd) {}
  string lbaStart;
  string lbaEnd;
};

class ScriptParam : public IParam {
 public:
  ScriptParam(TestShellCMD cmd, string number, string name)
      : IParam(cmd), scriptNumber(number), scriptName(name) {
    nScriptNumber = scriptNumber.empty() ? 0 : std::stoi(scriptNumber);
  }
  string scriptNumber;
  int nScriptNumber;
  string scriptName;
};
