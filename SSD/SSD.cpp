#include "SSD.h"

#include "EraseCommand.h"
#include "FlushCommand.h"
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
    case eFlushCmd:
      command = std::make_unique<FlushCommand>();
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

#if 0

bool SSD::ExecuteCommand(CommandType type, IParam* param) {
    std::unique_ptr<ICommand> command;

    switch (type) {
        case CommandType::WRITE:
            command = factory.CreateWriteCommand();
            break;
        case CommandType::FLUSH:
            command = factory.CreateFlushCommand();
            break;
        case CommandType::ERASE:
            command = factory.CreateEraseCommand();
            break;
        case CommandType::READ:
            command = factory.CreateReadCommand();
            break;
        default:
            return false;
    }

    if (!command->CheckPrecondition())
        return false;

    return command->Execute(param);
}

#endif
