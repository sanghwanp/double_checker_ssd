#include "CommandFactory.h"
#include "ICommandFactory.h"

ICommandFactory* ICommandFactory::GetInstance() {
  return CommandFactory::GetInstance();
}

// factory method to create commands based on the command type
IShellCommand* CommandFactory::CreateCommand(IParam& param, SSDInterface* ssd) {
  auto it = factories.find(param.eCmd);
  if (it != factories.end()) {
    return it->second->CreateCommand(param, ssd);
  }
  return nullptr;
}

// this part is register pattern implementation
// register a command factory for a specific command type
// This allows the CommandFactory to create commands dynamically
void CommandFactory::Register(TestShellCMD cmd, ICommandFactory* factory) {
  if (factories.find(cmd) == factories.end()) {
    factories[cmd] = factory;
  }

}
