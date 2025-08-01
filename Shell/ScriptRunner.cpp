#include "ScriptRunner.h"

#include <fstream>
#include <iostream>

#include "TestScriptCase1.h"
#include "TestScriptCase2.h"
#include "TestScriptCase3.h"
#include "TestScriptCase4.h"

ScriptRunner::ScriptRunner(SSDInterface* ssd, const std::string& scriptPath)
    : ssd(ssd), scriptPath(scriptPath) {}

void ScriptRunner::Run() {
  std::ifstream file(scriptPath.c_str());
  if (!file.is_open()) {
    std::cout << "Cannot open script file: " << scriptPath << "\n";
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) continue;

    // 1) 시작 메시지
    std::cout << line << " --- Run...";
    std::cout.flush();

    // 2) TestScript 호출
    bool ok = false;
    if (line == TEST1_LONG || line == TEST1_SHORT) {
      try {
        ok = TestScriptCase1(ssd).Call();
      } catch (...) {
        ok = false;
      }
    } else if (line == TEST2_LONG || line == TEST2_SHORT) {
      try {
        ok = TestScriptCase2(ssd).Call();
      } catch (...) {
        ok = false;
      }
    } else if (line == TEST3_LONG || line == TEST3_SHORT) {
      try {
        ok = TestScriptCase3(ssd).Call();
      } catch (...) {
        ok = false;
      }
    } else if (line == TEST4_LONG || line == TEST4_SHORT) {
      try {
        ok = TestScriptCase4(ssd).Call();
      } catch (...) {
        ok = false;
      }
    }
    else {
      std::cout << "INVALID SCRIPT\n";
      break;
    }

    if (ok) {
      std::cout << "Pass\n";
    } else {
      std::cout << "FAIL!\n";
      break;
    }
  }
}
