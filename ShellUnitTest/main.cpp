#include "gmock/gmock.h"

#if (MAIN_SELECT == 4)
using namespace testing;

int main() {
  InitGoogleMock();
  return RUN_ALL_TESTS();
}
#endif