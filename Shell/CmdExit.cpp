#include "CmdExit.h"

#include <iostream>

bool CommandExit::Call(const std::vector<std::string>& tokens) {
  if (tokens.size() != 1) {
    std::cout << "INVALID COMMAND\n";
    return false;
  }

  // ���� �ǻ縸 ��ȯ. ���� ����� main �Լ����� ����
  std::cout << "Shutting down\n";
  return true;
}
