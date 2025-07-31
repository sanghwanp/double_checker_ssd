#include "../Shell/MockSSD.h"
#include "gtest/gtest.h"

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

TEST(MockSSDTest, IsInvalidLBA_Valid) {
  MockSSD ssd;
  EXPECT_FALSE(ssd.IsInvalidLBA(0));
  EXPECT_FALSE(ssd.IsInvalidLBA(50));
}

TEST(MockSSDTest, IsInvalidLBA_InValid) {
  MockSSD ssd;
  EXPECT_TRUE(ssd.IsInvalidLBA(100));
  EXPECT_TRUE(ssd.IsInvalidLBA(200));
  EXPECT_TRUE(ssd.IsInvalidLBA(-10));
}

TEST(MockSSDTest, IsInvalidValue_Valid) {
  MockSSD ssd;
  EXPECT_FALSE(ssd.IsInvalidValue("0x12345678"));
  EXPECT_FALSE(ssd.IsInvalidValue("0xabcdef12"));
  EXPECT_FALSE(ssd.IsInvalidValue("0xABCDEF12"));
}

TEST(MockSSDTest, IsInvalidValue_InvalidPrefix) {
  MockSSD ssd;
  EXPECT_TRUE(ssd.IsInvalidValue("12345678"));
  EXPECT_TRUE(ssd.IsInvalidValue("0X12345678"));
  EXPECT_TRUE(ssd.IsInvalidValue("0y12345678"));
}

TEST(MockSSDTest, IsInvalidValue_WrongLength) {
  MockSSD ssd;
  EXPECT_TRUE(ssd.IsInvalidValue("0x1234567"));
  EXPECT_TRUE(ssd.IsInvalidValue("0x123456789"));
  EXPECT_TRUE(ssd.IsInvalidValue("0x"));
}

TEST(MockSSDTest, IsInvalidValue_InvalidChars) {
  MockSSD ssd;
  EXPECT_TRUE(ssd.IsInvalidValue("0x12345G7"));
  EXPECT_TRUE(ssd.IsInvalidValue("0x12#45678"));
  EXPECT_TRUE(ssd.IsInvalidValue("0x1234567!"));
}

TEST(MockSSDTest, Erase_Single) {
  MockSSD ssd;
  ssd.Write(10, "0x10000000");
  ssd.Write(11, "0x11000000");
  ssd.Write(12, "0x12000000");
  ssd.Write(13, "0x13000000");
  ssd.Write(14, "0x14000000");

  ssd.Erase(9, 1);
  ssd.Erase(12, 1);

  EXPECT_EQ(ssd.Read(9), "0x00000000");
  EXPECT_EQ(ssd.Read(10), "0x10000000");
  EXPECT_EQ(ssd.Read(11), "0x11000000");
  EXPECT_EQ(ssd.Read(12), "0x00000000");
  EXPECT_EQ(ssd.Read(13), "0x13000000");
  EXPECT_EQ(ssd.Read(14), "0x14000000");
  EXPECT_EQ(ssd.Read(15), "0x00000000");
}

TEST(MockSSDTest, Erase_Double) {
  MockSSD ssd;
  ssd.Write(10, "0x10000000");
  ssd.Write(11, "0x11000000");
  ssd.Write(12, "0x12000000");
  ssd.Write(13, "0x13000000");
  ssd.Write(14, "0x14000000");

  ssd.Erase(12, 2);

  EXPECT_EQ(ssd.Read(9), "0x00000000");
  EXPECT_EQ(ssd.Read(10), "0x10000000");
  EXPECT_EQ(ssd.Read(11), "0x11000000");
  EXPECT_EQ(ssd.Read(12), "0x00000000");
  EXPECT_EQ(ssd.Read(13), "0x00000000");
  EXPECT_EQ(ssd.Read(14), "0x14000000");
  EXPECT_EQ(ssd.Read(15), "0x00000000");
}

TEST(MockSSDTest, Erase_All) {
  MockSSD ssd;
  ssd.Write(10, "0x10000000");
  ssd.Write(11, "0x11000000");
  ssd.Write(12, "0x12000000");
  ssd.Write(13, "0x13000000");
  ssd.Write(14, "0x14000000");

  ssd.Erase(10, 5);

  EXPECT_EQ(ssd.Read(10), "0x00000000");
  EXPECT_EQ(ssd.Read(11), "0x00000000");
  EXPECT_EQ(ssd.Read(12), "0x00000000");
  EXPECT_EQ(ssd.Read(13), "0x00000000");
  EXPECT_EQ(ssd.Read(14), "0x00000000");
}

TEST(MockSSDTest, Erase_Invalid) {
  MockSSD ssd;
  ssd.Write(10, "0x10000000");
  ssd.Write(11, "0x11000000");
  ssd.Write(12, "0x12000000");
  ssd.Write(13, "0x13000000");
  ssd.Write(14, "0x14000000");

  ssd.Erase(8, 11);

  EXPECT_EQ(ssd.Read(10), "0x10000000");
  EXPECT_EQ(ssd.Read(11), "0x11000000");
  EXPECT_EQ(ssd.Read(12), "0x12000000");
  EXPECT_EQ(ssd.Read(13), "0x13000000");
  EXPECT_EQ(ssd.Read(14), "0x14000000");
}

TEST(MockSSDTest, Erase_InvalidLBA) {
  MockSSD ssd;
  ssd.Write(0, "0x10000000");

  ssd.Erase(-1, 2);

  EXPECT_EQ(ssd.Read(0), "0x10000000");
}

TEST(MockSSDTest, Erase_InvalidRange) {
  MockSSD ssd;
  ssd.Write(99, "0x10000000");

  ssd.Erase(99, 2);

  EXPECT_EQ(ssd.Read(99), "0x10000000");
}
