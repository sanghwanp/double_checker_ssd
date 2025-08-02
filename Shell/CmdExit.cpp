#include "CmdExit.h"

#include <iostream>

bool CommandExit::Call(IParam& param) {

  if (param.eCmd == eInvalidCmd) return false;
  // 종료 의사만 반환. 실제 종료는 main 함수에서 진행
  std::cout << "Shutting down\n";
  return true;
}
