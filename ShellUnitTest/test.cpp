#include "gmock/gmock.h"
#include "../Shell/Cal.h"
TEST(SSDTS, TC1) {

  Cal obj;
  obj.run();

  int ret = 0;
  EXPECT_EQ(ret, 0);
}