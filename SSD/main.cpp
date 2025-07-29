#include "gmock/gmock.h"

using namespace testing;
#if (MAIN_SELECT == 1)
int main() {
  InitGoogleMock();
  return RUN_ALL_TESTS();
}
#endif