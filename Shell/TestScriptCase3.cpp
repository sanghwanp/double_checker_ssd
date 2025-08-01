#include "TestScriptCase3.h"

#include <iostream>

TestScriptCase3::TestScriptCase3(SSDInterface* ssdinterface)
    : ITestScriptCase(ssdinterface, 3, "WriteReadAging") {}

bool TestScriptCase3::Call() {
  /*
  Loop 200회
  1. 0번 LBA에 랜덤값을 적는다.
  2. 99번 LBA에 랜덤값을 적는다.
  3. LBA 0번과 99번, ReadCompare를 수행
 */
  std::string data;

  for (int repeat_count = 0; repeat_count < 200; repeat_count += 5) {
    data = GetRandomInputData();

    ssd->Write(0, data);
    ssd->Write(99, data);

    if (ReadCompare(std::to_string(0), data) != true) {
      return false;
    }
    if (ReadCompare(std::to_string(99), data) != true) {
      return false;
    }
  }

  return true;
}
