#include "CmdHelp.h"

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

typedef std::tuple<std::string, std::string, std::string> HelpString;

namespace {
static const std::vector<HelpString> helpString = {
        {"write", "write [LBA] [Value]", "지정한 LBA에 값을 기록합니다."},
        {"read", "read [LBA]", "지정한 LBA에서 값을 읽습니다."},
        {"fullwrite", "fullwrite [Value]", "모든 LBA에 동일한 값을 기록합니다."},
        {"fullread", "fullread", "모든 LBA를 읽고 출력합니다."},
        {"erase", "erase [LBA]  [SIZE]", "특정LBA 부터 특정 Size까지 값을 삭제합니다."},
        {"erase_range", "erase_range [Start LBA]  [End LBA]", "Start LBA 부터 End LBA 까지 값을 삭제합니다."},
        {"flush", "flush", "Command Buffer에 있는 모든 명령어들을 수행하여 Buffer 전체 비웁니다."},
        {"help", "help", "도움말을 출력합니다."},
        {"exit", "exit", "셸을 종료합니다."},
        {"", "", ""},
        {"test script 1", "1_FullWriteAndReadCompare or 1_", "test script 1을 실행합니다."},
        {"test script 2", "2_PartialLBAWrite or 2_", "test script 2를 실행합니다."},
        {"test script 3", "3_WriteReadAging or 3_", "test script 3을 실행합니다."},
        {"test script 4", "4_EraseAndWriteAging or 4_", "test script 4를 실행합니다."}
    };
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
  std::cout << " - 팀장: 박상환\n";
  std::cout << " - 팀원: 곽예나, 김연우, 박시은, 양동혁, 정주성\n\n";

  std::cout << "[Command Usage]\n";
  for (const auto& str : helpString) {
    HelpPrint(str);
  }

  return true;
}
