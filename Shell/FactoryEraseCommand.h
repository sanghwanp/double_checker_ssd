#pragma once
#include "ICommandFactory.h"

class FactoryEraseCommand : public ICommandFactory {
public:
    FactoryEraseCommand() = default;
    IShellCommand* CreateCommand(IParam& param, SSDInterface* ssd) override;
};
