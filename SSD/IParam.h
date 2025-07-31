#pragma once
#include "Types.h"

#define interface struct
interface IArguments {
 public:
  virtual ~IArguments() = default;
  virtual unsigned int GetLba() const = 0;
  virtual void Parse(const std::string& cmdStr) = 0;
};

class IParam {
 public:
  IParam(CMD_TYPE cmd) : eCmd(cmd) {}
  virtual ~IParam() {}

  CMD_TYPE eCmd;
};

class WriteParam : public IParam {
 public:
  WriteParam(CMD_TYPE cmd, LBA lba, DATA data)
      : IParam(cmd), lba(lba), data(data) {}
  LBA lba;
  DATA data;
};

class ReadParam : public IParam {
 public:
  ReadParam(CMD_TYPE cmd, LBA lba) : IParam(cmd), lba(lba) {}
  LBA lba;
};
