#include "SSD.h"
#include "ReadCommand.h"
#include "WriteCommand.h"

SSD SSD::instance;

SSD::SSD() : cache(100) {
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
      command = std::make_unique<ICommand>();
      break;
  }

  command->Execute(param);
}
