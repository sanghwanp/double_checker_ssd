#include "SSD.h"

#include "EraseCommand.h"
#include "FlushCommand.h"
#include "ReadCommand.h"
#include "WriteCommand.h"

SSD::SSD()
    : fileDriver(FileDriver::GetInstance()),
      bufferHandler(CommandBufferHandler::GetInstance()),
      commandFactory(CommandFactory::GetInstance()) {}

void SSD::Run(vector<string> args) {
  IParam *cmd;
  cmd = parser.Parse(args);
  if (cmd->eCmd == eInvalidCmd || !ExecuteCommand(cmd))
    fileDriver->StoreError();
}

bool SSD::ExecuteCommand(IParam* param) {
  std::unique_ptr<ICommand> command = commandFactory->GetCommand(param->eCmd);
  return (command && command->Execute(param));
}

unsigned int SSD::GetCachedData(unsigned int lba) {
  return fileDriver->GetBufferData(lba);
}
