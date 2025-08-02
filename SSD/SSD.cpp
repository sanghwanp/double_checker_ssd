#include "SSD.h"

#include "EraseCommand.h"
#include "ReadCommand.h"
#include "WriteCommand.h"
#include "FlushCommand.h"

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

  bool useBuffer = false;
  switch (param->eCmd) {
    case eWriteCmd:
      command = std::make_unique<WriteCommand>();
      useBuffer = true;
      break;
    case eReadCmd:
      command = std::make_unique<ReadCommand>();
      useBuffer = false;
      break;
    case eEraseCmd:
      command = std::make_unique<EraseCommand>();
      useBuffer = true;
      break;
    case eFlushCmd:
      command = std::make_unique<FlushCommand>();
      useBuffer = false;
      break;
    default:
      command = std::make_unique<ICommand>();
      useBuffer = false;
      break;
  }

  if (false == command->Execute(param, useBuffer)) {
    filedriver->SaveFile(OUTPUT_FILE_NAME, "ERROR");
  }
}

unsigned int SSD::GetCachedData(unsigned int lba) {
  return filedriver->GetBufferData(lba);
}
