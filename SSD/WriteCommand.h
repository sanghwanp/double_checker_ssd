#pragma once

#include "ICommand.h"
#include "FileDriver.h"
#include "CommandBufferHandler.h"
#include "CommandFactory.h"

class WriteCommand : public ICommand {
public:
    WriteCommand(FileDriver* fileDriver,
                 CommandBufferHandler* bufferHandler,
                 CommandFactory* factory);

    bool Execute(IParam* param) override;
    bool CheckPrecondition() override;

private:
    FileDriver* fileDriver;
    CommandBufferHandler* bufferHandler;
    CommandFactory* factory;
};
#if 0

#pragma once

#include "CommandBufferHandler.h"
#include "CommandFactory.h"
#include "FileDriver.h"
#include "ICommand.h"

class WriteCommand : public ICommand {
public:
    WriteCommand(FileDriver* fileDriver,
                 CommandBufferHandler* bufferHandler,
                 CommandFactory* factory);

    bool Execute(IParam* param) override;
    bool CheckPrecondition() override;

private:
    FileDriver* fileDriver;
    CommandBufferHandler* bufferHandler;
    CommandFactory* factory;
};

#endif
