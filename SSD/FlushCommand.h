#pragma once
#include "ICommand.h"

class FlushCommand : public ICommand {
 public:
  explicit FlushCommand(CommandFactory* factory = nullptr) : factory(factory) {}
  bool Execute(IParam* param) override;
  void Flush(std::vector<CommandBufferEntry> entry);
  void SaveFile();

  CommandFactory* factory;
};


#if 0
#pragma once

#include "FileDriver.h"
#include "ICommand.h"

class FlushCommand : public ICommand {
public:
    explicit FlushCommand(FileDriver* fileDriver);

    bool Execute(IParam* param) override;
    bool CheckPrecondition() override;

private:
    FileDriver* fileDriver;
};
#endif
