#pragma once
#include "ICommandFactory.h"

class FactoryWriteCommand : public ICommandFactory {
public:
    FactoryWriteCommand() = default;
    IShellCommand* CreateCommand(IParam& param, SSDInterface* ssd) override;
};
