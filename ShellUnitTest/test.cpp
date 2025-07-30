#include "gtest/gtest.h"
#include "../Shell/MockSSD.h"

TEST(MockSSDTest, WriteThenReadSameLBA) {
  MockSSD ssd;
  ssd.Write(10, "0x0000ABCD");
  EXPECT_EQ(ssd.Read(10), "0x0000ABCD");
}

TEST(MockSSDTest, ReadInvalidLBA_ReturnsDefault) {
  MockSSD ssd;
  ssd.Write(5, "0x0000ABCD");
  EXPECT_EQ(ssd.Read(6), "0x00000000");
}

TEST(MockSSDTest, OverwriteSameLBA) {
  MockSSD ssd;
  ssd.Write(2, "1234");
  ssd.Write(2, "5678");
  EXPECT_EQ(ssd.Read(2), "5678");
}