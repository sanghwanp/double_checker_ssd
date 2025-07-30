#pragma once

#include "CommonConfig.h"

enum CommandType {
  CMD_INIT = 0,
  CMD_READ,
  CMD_WRITE,
  CMD_OTHER,
};

class CommandArguments {
 public:
  CommandArguments() : cmdType{CMD_INIT}, lba{0}, data{0} {}
  CommandArguments(CommandType cmdType, int lba, uint data = 0)
      : cmdType{cmdType}, lba{lba}, data{data} {}

  CommandType cmdType;
  int lba;
  uint data;
};

class ICommand {
 public:
  virtual void Run(CommandArguments args) = 0;
};