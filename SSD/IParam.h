#pragma once
#include <string>

#define interface struct
interface IArguments {
 public:
  virtual ~IArguments() = default;
  virtual unsigned int GetLba() const = 0;
  virtual void Parse(const std::string& cmdStr) = 0;
};

using std::string;

enum SSD_CMD { eWriteCmd, eReadCmd, eInvalidCmd };

class IParam {
 public:
  IParam(SSD_CMD cmd) : eCmd(cmd) {}
  virtual ~IParam() {}

  SSD_CMD eCmd;
};

class WriteParam : public IParam {
 public:
  WriteParam(SSD_CMD cmd, string lba, string data)
      : IParam(cmd), lba(lba), data(data) {}
  string lba;
  string data;
};

class ReadParam : public IParam {
 public:
  ReadParam(SSD_CMD cmd, string lba) : IParam(cmd), lba(lba) {}
  string lba;
};
