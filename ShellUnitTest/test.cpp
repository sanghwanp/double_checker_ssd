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
  ssd.Write(2, "0x00001234");
  ssd.Write(2, "0x00005678");
  EXPECT_EQ(ssd.Read(2), "0x00005678");
}

TEST(MockSSD, Overwrite_ShouldUpdateValue) {
  MockSSD ssd;
  ssd.Write(2, "0x12345678");
  ssd.Write(2, "0x87654321");
  EXPECT_EQ(ssd.Read(2), "0x87654321");
}

TEST(MockSSD, OverwriteThenEmptyLBA_ReadReturnsCorrectValues) {
  MockSSD ssd;
  ssd.Write(5, "0x11111111");
  ssd.Write(5, "0x22222222");

  EXPECT_EQ(ssd.Read(5), "0x22222222");
  EXPECT_EQ(ssd.Read(6), "0x00000000");
}
TEST(MockSSD, Read_EmptyLBA_ShouldReturnDefault) {
  MockSSD ssd;
  EXPECT_EQ(ssd.Read(99), "0x00000000");
}

TEST(MockSSD, MultipleLBA_WritesAndReads) {
  MockSSD ssd;
  ssd.Write(0, "0xAAAAAAAA");
  ssd.Write(10, "0xBBBBBBBB");
  ssd.Write(50, "0xCCCCCCCC");

  EXPECT_EQ(ssd.Read(0), "0xAAAAAAAA");
  EXPECT_EQ(ssd.Read(10), "0xBBBBBBBB");
  EXPECT_EQ(ssd.Read(50), "0xCCCCCCCC");
}