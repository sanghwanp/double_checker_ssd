#pragma once
#include <string>
using std::string;
enum TestShellCMD {
  eWriteCmd,
  eReadCmd,
  eHelpCmd,
  eExitCmd,
  eFullwrite,
  eFullread,
  eInvalidCmd
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