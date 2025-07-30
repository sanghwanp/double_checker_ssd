#include "CmdHelp.h"

#include <iostream>

bool CommandHelp::Call(const std::vector<std::string>& program) {
  std::cout << "[Team Info] CRA Double Checker Team\n";
  std::cout << " - 팀장: 박상환\n";
  std::cout << " - 팀원: 곽예나, 김연우, 박시은, 양동혁, 정주성\n\n";

  std::cout << "[Command Usage]\n";
  std::cout << "1. write [LBA] [Value]     : 지정한 LBA에 값을 기록합니다.\n";
  std::cout << "2. read [LBA]              : 지정한 LBA에서 값을 읽습니다.\n";
  std::cout << "3. fullwrite [Value]       : 모든 LBA에 동일한 값을 기록합니다.\n";
  std::cout << "4. fullread                : 모든 LBA를 읽고 출력합니다.\n";
  std::cout << "5. help                    : 도움말을 출력합니다.\n";
  std::cout << "6. exit                    : 셸을 종료합니다.\n";
  return true;
}