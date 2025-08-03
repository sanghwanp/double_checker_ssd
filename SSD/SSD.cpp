#include "SSD.h"

SSD::SSD(FileDriver* fileDriver, CommandBufferHandler* bufferHandler,
         CommandFactory* commandFactory)
    : fileDriver(fileDriver),
      bufferHandler(bufferHandler),
      commandFactory(commandFactory) {}

void SSD::Run(IParam* cmd) {
  if (!ExecuteCommand(cmd)) fileDriver->StoreError();
}

bool SSD::ExecuteCommand(IParam* param) {
  std::unique_ptr<ICommand> command = commandFactory->GetCommand(param->eCmd);
  return (command && command->Execute(param));
}

unsigned int SSD::GetCachedData(unsigned int lba) {
  return fileDriver->GetBufferData(lba);
}
