#include "TestScriptCase1.h"

#include <iostream>

TestScriptCase1::TestScriptCase1(SSDInterface* ssdinterface)
    : ITestScriptCase(ssdinterface, 1) {}

bool TestScriptCase1::Call() {
  /*
1. 0 ~ 4번 LBA까지 Write 명령어를 수행한다
2. 0 ~ 4번 LBA까지 ReadCompare 수행
3. 5 ~ 9번 LBA까지 다른 값으로Write 명령어를 수행한다
4. 5 ~ 9번 LBA까지 ReadCompare 수행
5. 10 ~ 14번 LBA까지 다른 값으로 Write 명령어를 수행한다.
6. 10 ~ 14번 LBA까지 ReadCompare 수행
7. 위와같은규칙으로전체영역에대해Full Write + Read Compare를 수행한다
*/
  std::string data;

  for (int repeat_count = 0; repeat_count < 100; repeat_count += 5) {
    data = GetRandomInputData();
    for (int write_count = 0; write_count < 5; ++write_count) {
      ssd->Write(repeat_count + write_count, data);
    }

    for (int read_count = 0; read_count < 5; ++read_count) {
      if (ReadCompare(std::to_string(repeat_count + read_count), data) !=
          true) {
        return false;
      }
    }
  }

  return true;
}
