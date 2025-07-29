#include "gmock/gmock.h"

#if (MAIN_SELECT == 2)
using namespace testing;
int main() {
  InitGoogleMock();
  return RUN_ALL_TESTS();
}
#endif
