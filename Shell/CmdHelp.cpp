#include "CmdHelp.h"

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

typedef std::tuple<std::string, std::string, std::string> HelpString;

namespace {
static const std::vector<HelpString> helpString = {
    {"write", "write [LBA] [Value]", "Write the specified value to the given LBA."},
    {"read", "read [LBA]", "Read the value from the specified LBA."},
    {"fullwrite", "fullwrite [Value]", "Write the same value to all LBAs."},
    {"fullread", "fullread", "Read and print all LBAs."},
    {"erase", "erase [LBA]  [SIZE]", "Delete values from the specified LBA for the given size."},
    {"erase_range", "erase_range [Start LBA]  [End LBA]", "Delete values from Start LBA to End LBA."},
    {"flush", "flush", "Execute all commands in the Command Buffer and clear the entire buffer."},
    {"help", "help", "Display help information."},
    {"exit", "exit", "Exit the shell."},
    {"", "", ""},
    {"test script 1", "1_FullWriteAndReadCompare or 1_", "Execute test script 1."},
    {"test script 2", "2_PartialLBAWrite or 2_", "Execute test script 2."},
    {"test script 3", "3_WriteReadAging or 3_", "Execute test script 3."},
    {"test script 4", "4_EraseAndWriteAging or 4_", "Execute test script 4."}};
}

static void HelpPrint(const HelpString& str) {
  if (std::get<0>(str).empty()) {
    std::cout << std::endl;
  } else {
    std::cout << "    " << std::get<0>(str) << std::endl;
    std::cout << "        " << "Usage : " << std::get<1>(str) << std::endl;
    std::cout << "        " << "Comment : " << std::get<2>(str) << std::endl;
  }
}

bool CommandHelp::Call(const std::vector<std::string>& program) {
  std::cout << "[Team Info] CRA Double Checker Team\n";
  std::cout << " - Team leader: Sanghwan Park\n";
  std::cout << " - Team members: Yena Gwak, Yeonwoo Kim, Sieun Park, Donghyuk Yang, Jooseong Jeong\n\n";

  std::cout << "[Command Usage]\n";
  for (const auto& str : helpString) {
    HelpPrint(str);
  }

  return true;
}
