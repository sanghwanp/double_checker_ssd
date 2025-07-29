#include "SSD.h"
#include "gmock/gmock.h"
TEST(SSD_TS, BasicReadOperation) {
  SSD ssd;
  const int NO_DATA = 0x00000000;
  const int lba = 0;
  unsigned int value = ssd.read(lba);

  EXPECT_EQ(value, NO_DATA);
}