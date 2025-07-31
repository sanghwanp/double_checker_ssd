#include "SSD.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

SSD SSD::instance;

SSD::SSD() {
  commandFactory = CommandFactory::GetInstance();
  filedriver = FileDriver::GetInstance();
}

void SSD::Run(vector<string> args) {
  IParam *cmd;
  cmd = parser.Parse(args);

  ExecuteCommand(cmd);

}

void SSD::ExecuteCommand(IParam *param) {
  std::unique_ptr<ICommand> command;

  switch (param->eCmd) {
    case eWriteCmd:
      command = std::make_unique<WriteCommand>();
      break;
    case eReadCmd:
      command = std::make_unique<ReadCommand>();
      break;
    default:
      std::cerr << "Invalid command\n";
      command = std::make_unique<ICommand>();
      break;
  }

  command->Execute(param);
}

unsigned int SSD::GetCachedData(unsigned int lba) {
  if (lba >= SSDConfig::kStorageSize) {
    throw std::invalid_argument("Invalid LBA access");
  }
  return cache[lba];
}
