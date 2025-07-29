#include "../SSD/cal.h"
#include "gmock/gmock.h"

TEST(TS, TC1){
  cal obj;

  obj.run();

  int ret = 0;
  EXPECT_EQ(ret, 0);
}