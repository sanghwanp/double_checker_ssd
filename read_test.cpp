// RED
TEST(TS, TC1) {
  const int NO_DATA = 0x00000000;
  const int lba = 0;
  int value = ssd.read(lba);

  EXPECT_EQ(value, NO_DATA);
}