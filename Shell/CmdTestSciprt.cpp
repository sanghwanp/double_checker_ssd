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

std::string CommandTestScript::Call(IParam& param) {
  const ScriptParam& scriptParam = dynamic_cast<const ScriptParam&>(param);
  const int requestedNumber = scriptParam.nScriptNumber;

  if (!(requestedNumber >= 1 && requestedNumber <= cases.size())) {
    return "INVALID_COMMAND";
  }

  const std::string& requestedFullName = scriptParam.scriptName;
  if ((requestedFullName != cases[requestedNumber - 1]->GetFullName()) &&
      (requestedFullName !=
          std::to_string(cases[requestedNumber - 1]->GetNumber()) + "_")) {
    return "INVALID_COMMAND";
  }

  if (cases[scriptParam.nScriptNumber - 1]->Call()) {
    return ITestScriptCase::TEST_SCRIPT_PASS_OUTPUT;
  }
  else {
    return ITestScriptCase::TEST_SCRIPT_FAIL_OUTPUT;
  }
}
