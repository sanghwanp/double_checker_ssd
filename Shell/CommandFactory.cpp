#include "CommandFactory.h"
#include "ICommandFactory.h"
#include "ILogger.h"

ICommandFactory* ICommandFactory::GetInstance() {
  return CommandFactory::GetInstance();
}

// factory method to create commands based on the command type
IShellCommand* CommandFactory::CreateCommand(IParam& param, SSDInterface* ssd) {
  if (param.eCmd == eInvalidCmd) {
        ILogger::GetInstance()->LogPrint(
            "CommandFactory::CreateCommand",
            "Invalid command" + std::to_string(param.eCmd), false);
        return nullptr;
  }
  auto it = factories.find(param.eCmd);
  if (it != factories.end()) {
    return it->second->CreateCommand(param, ssd);
  }
    ILogger::GetInstance()->LogPrint(
        "CommandFactory::CreateCommand",
      "No factory registered for command: " + std::to_string(param.eCmd),false);
  return nullptr;
}

// this part is register pattern implementation
// register a command factory for a specific command type
// This allows the CommandFactory to create commands dynamically
void CommandFactory::Register(TestShellCMD cmd, ICommandFactory* factory) {
  if (factories.find(cmd) == factories.end()) {
    ILogger::GetInstance()->LogPrint(
        "CommandFactory::Register", "Registering command factory for command: " + std::to_string(cmd),
        false);
    factories[cmd] = factory;
  }

}
