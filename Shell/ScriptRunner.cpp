#include "ScriptRunner.h"

ScriptRunner::ScriptRunner(std::istream& in) : in(in) {}

void ScriptRunner::run() {
  std::string cmd;
  while (std::getline(in, cmd)) {
    if (cmd.empty()) continue;

    bool result = true;

    if (cmd == TEST_SCRIPT_1_LONG || cmd == TEST_SCRIPT_1_SHORT) {
      std::cout << TEST_SCRIPT_1_LONG << PRINT_RUN_COMMAND;
      // TODO: Call TestScript Four Class
      // result = TestScript1.Run();
    } else if (cmd == TEST_SCRIPT_2_LONG || cmd == TEST_SCRIPT_2_SHORT) {
      std::cout << TEST_SCRIPT_1_LONG << PRINT_RUN_COMMAND;
      // TODO: Call TestScript Four Class
      // result = TestScript2.Run();
    } else if (cmd == TEST_SCRIPT_3_LONG || cmd == TEST_SCRIPT_3_SHORT) {
      std::cout << TEST_SCRIPT_1_LONG << PRINT_RUN_COMMAND;
      // TODO: Call TestScript Four Class
      // result = TestScript3.Run();
    } else if (cmd == TEST_SCRIPT_4_LONG || cmd == TEST_SCRIPT_4_SHORT) {
      std::cout << TEST_SCRIPT_1_LONG << PRINT_RUN_COMMAND;
      // TODO: Call TestScript Four Class
      // result = TestScript4.Run();
    } else {
      std::cout << cmd << PRINT_INVALID_COMMAND << "\n";
      break;
    }

    if (result) {
      std::cout << PRINT_PASS_COMMAND << "\n ";
    } else {
      std::cout << PRINT_FAIL_COMMAND << "\n";
      break;
    }
  }
}