#include "CommandFactory.h"

#include "CmdErase.h"
#include "CmdEraseRange.h"
#include "CmdExit.h"
#include "CmdFlush.h"
#include "CmdFullRead.h"
#include "CmdFullWrite.h"
#include "CmdHelp.h"
#include "CmdRead.h"
#include "CmdTestScript.h"
#include "CmdWrite.h"
#include "MockSSD.h"
#include "RealSSD.h"

ICommandFactory* ICommandFactory::GetInstance() {
  return CommandFactory::GetInstance();
}

CommandFactory::CommandFactory()
{

}

IShellCommand* CommandFactory::CreateCommand(IParam& param, SSDInterface* ssd) {
  IShellCommand* command = nullptr;

  switch (param.eCmd) {
    case eWriteCmd:
      command = new CommandWrite(ssd);
      break;
    case eReadCmd:
      command = new CommandRead(ssd);
      break;
    case eEraseCmd:
      command = new CommandErase(ssd);
      break;
    case eEraseRangeCmd:
      command = new CommandEraseRange(ssd);
      break;
    case eFlushCmd:
      command = new CommandFlush(ssd);
      break;
    case eFullread:
      command = new CommandFullRead(ssd);
      break;
    case eFullwrite:
      command = new CommandFullWrite(ssd);
      break;
    case eHelpCmd:
      command = new CommandHelp();
      break;
    case eExitCmd:
      command = new CommandExit();
      break;
    default:
        // nothing to do here
      break;
  }

  return command;
}
