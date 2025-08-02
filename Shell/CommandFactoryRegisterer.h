#pragma once
#include "CommandFactory.h"
class CommandFactoryRegisterer {
public:
    inline CommandFactoryRegisterer(TestShellCMD cmd, ICommandFactory* factory) {
        CommandFactory::GetInstance()->Register(cmd, factory);
    }
};
