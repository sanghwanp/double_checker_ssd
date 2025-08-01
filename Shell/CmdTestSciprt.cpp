#include "CmdTestScript.h"
#include "TestScriptCase1.h"
#include "TestScriptCase2.h"
#include "TestScriptCase3.h"
#include "TestScriptCase4.h"

CommandTestScript::CommandTestScript(SSDInterface* ssdInterface)
    : ssd(ssdInterface) {
  cases.push_back(std::make_unique<TestScriptCase1>(ssdInterface));
  cases.push_back(std::make_unique<TestScriptCase2>(ssdInterface));
  cases.push_back(std::make_unique<TestScriptCase3>(ssdInterface));
  cases.push_back(std::make_unique<TestScriptCase4>(ssdInterface));
}

bool CommandTestScript::Call(const IParam& param) {
  const ScriptParam& scriptParam = dynamic_cast<const ScriptParam&>(param);
  if (scriptParam.nScriptNumber - 1 < 0) {
    return false;
  }
  return cases[scriptParam.nScriptNumber - 1]->Call();
}
