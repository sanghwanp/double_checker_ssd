#include "SSD.h"

#include "EraseCommand.h"
#include "ReadCommand.h"
#include "WriteCommand.h"

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
    case eEraseCmd:
      command = std::make_unique<EraseCommand>();
      break;
    default:
      command = std::make_unique<ICommand>();
      break;
  }

  if (false == command->Execute(param)) {
    filedriver->SaveFile(OUTPUT_FILE_NAME, "ERROR");
  }
}

unsigned int SSD::GetCachedData(unsigned int lba) {
  return filedriver->GetBufferData(lba);
}
