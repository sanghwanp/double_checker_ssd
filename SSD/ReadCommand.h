#pragma once
#include "ICommand.h"

class ReadCommand : public ICommand {
 public:
  explicit ReadCommand(CommandFactory* factory = nullptr) : factory(factory) {}
  bool Execute(IParam* param) override;
  bool CheckPrecondition() override;
  void ReadData(const std::string& outval);
  std::string ReadCommand::ToString(unsigned int val);

 private:
  CommandFactory* factory;
  ReadParam* readParam;
};


#if 0
#pragma once

#include "FileDriver.h"
#include "ICommand.h"

class ReadCommand : public ICommand {
public:
    explicit ReadCommand(FileDriver* fileDriver);

    bool Execute(IParam* param) override;
    bool CheckPrecondition() override;

private:
    FileDriver* fileDriver;
};

#endif
