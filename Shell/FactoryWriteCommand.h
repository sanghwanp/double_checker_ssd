#pragma once
#include "ICommandFactory.h"

class FactoryWriteCommand : public ICommandFactory {
public:
    FactoryWriteCommand() = default;
    IShellCommand* CreateCommand(IParam& param, SSDInterface* ssd) override;
};

class FactoryDoubleCommand : public ICommandFactory {
public:
    FactoryDoubleCommand() = default;
    IShellCommand* CreateCommand(IParam& param, SSDInterface* ssd) override;
};
