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

static MockSSD MockssdDriver;
static RealSSD RealssdDriver;

CommandFactory::CommandFactory()
{
#ifdef UNIT_TEST
  ssdInterface = &MockssdDriver;
#else
  ssdInterface = &RealssdDriver;
#endif
}

IShellCommand* CommandFactory::CreateCommand(IParam& param) {
  IShellCommand* command = nullptr;

  switch (param.eCmd) {
    case eWriteCmd:
      command = new CommandWrite(ssdInterface);
      break;
    case eReadCmd:
      command = new CommandRead(ssdInterface);
      break;
    case eEraseCmd:
      command = new CommandErase(ssdInterface);
      break;
    case eEraseRangeCmd:
      command = new CommandEraseRange(ssdInterface);
      break;
    case eFlushCmd:
      command = new CommandFlush(ssdInterface);
      break;
    case eFullread:
      command = new CommandFullRead(ssdInterface);
      break;
    case eFullwrite:
      command = new CommandFullWrite(ssdInterface);
      break;
    case eScriptCmd:
      command = new CommandTestScript(ssdInterface);
      break;
    case eHelpCmd:
      command = new CommandHelp();
      break;
    case eExitCmd:
      command = new CommandExit();
      break;
    default:

      // Handle unknown command
      break;
  }

  return command;
}
