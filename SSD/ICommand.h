#pragma once

class IParam;

class ICommand {
 public:
  ICommand() {}
  virtual ~ICommand() = default;

  virtual bool Execute(IParam* param) = 0;
  virtual bool CheckPrecondition() = 0;
};
