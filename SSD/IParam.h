#pragma once
#include "Types.h"

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

class EraseParam : public IParam {
 public:
  EraseParam(CMD_TYPE cmd, LBA lba, SIZE_E size)
      : IParam(cmd), lba(lba), size(size) {}
  LBA lba;
  SIZE_E size;
};

class FlushParam : public IParam {
 public:
  FlushParam(CMD_TYPE cmd) : IParam(cmd) {}
};
