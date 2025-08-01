#include "TestScriptCase4.h"

#include <iostream>

TestScriptCase4::TestScriptCase4(SSDInterface* ssdinterface)
    : ITestScriptCase(ssdinterface, 4, "EraseAndWriteAging") {}

bool TestScriptCase4::Call() {
  /*
  Loop 30회
01. 2번 LBA Write
02. 2번 LBA OverWrite
03. 2 ~ 4번 LBA 삭제
04. 2 ~ 4번 ReadCompare

05. 4번 LBA Write
06. 4번 LBA OverWrite
07. 4 ~ 6번 LBA 삭제
08. 4 ~ 6번 ReadCompare

09. 6번 LBA Write
10. 6번 LBA OverWrite
11. 6 ~ 8번 LBA 삭제
12. 6 ~ 8번 ReadCompare

13. 전체LBA 영역에대해 같은규칙으로수행
  */

  std::string data = GetRandomInputData();
  const std::string zero = "0x00000000";

  for (int repeat_count = 0; repeat_count < 30; repeat_count += 5) {
    for (int lba_site = 2; lba_site < 100; lba_site += 2) {
      ssd->Write(lba_site, data);
      ssd->Write(lba_site, data);

      if (lba_site != 98) {
        ssd->Erase(lba_site, 3);
      } else {
        ssd->Erase(lba_site, 2);
      }

      for (int read_count = 0; read_count < 3; ++read_count) {
        if (lba_site + read_count > 99) break;
        if (ReadCompare(std::to_string(lba_site + read_count), zero) != true) {
          return false;
        }
      }
    }
  }

  return true;
}
