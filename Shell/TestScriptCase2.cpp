#include "TestScriptCase2.h"

#include <iostream>

TestScriptCase2::TestScriptCase2(SSDInterface* ssdinterface)
    : ITestScriptCase(ssdinterface, 2, "PartialLBAWrite") {}

bool TestScriptCase2::Call() {
  /*
  Loop는 30회
  1. 4번 LBA에 값을적는다.
  2. 0번 LBA에 같은 값을 적는다.
  3. 3번 LBA에 같은 값을 적는다.
  4. 1번 LBA에 같은 값을 적는다.
  5. 2번 LBA에 같은 값을 적는다.
  6. LBA 0 ~4번, ReadCompare
*/
  std::string data;

  for (int repeat_count = 0; repeat_count < 30; ++repeat_count) {
    data = GetRandomInputData();
    ssd->Write(4, data);
    ssd->Write(0, data);
    ssd->Write(3, data);
    ssd->Write(1, data);
    ssd->Write(2, data);

    for (int read_count = 0; read_count < 5; ++read_count) {
      if (ReadCompare(std::to_string(read_count), data) !=
          true) {
        return false;
      }
    }
  }

  return true;
}
