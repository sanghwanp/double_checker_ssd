#pragma once
#include "ICommand.h"

class EraseCommand : public ICommand {
 public:
  explicit EraseCommand(CommandFactory* factory = nullptr) : factory(factory) {}
  bool Execute(IParam* param) override;
  bool CheckPrecondition() override;

  void UpdateDataBuffer();
  void SaveCommandBuffer();
  void SaveFile();

 private:
  CommandFactory* factory;
  EraseParam* eraseParam;
};


#if 0
#pragma once

#include "FileDriver.h"
#include "ICommand.h"

class EraseCommand : public ICommand {
public:
    explicit EraseCommand(FileDriver* fileDriver);

    bool Execute(IParam* param) override;
    bool CheckPrecondition() override;

private:
    FileDriver* fileDriver;
};

#endif
