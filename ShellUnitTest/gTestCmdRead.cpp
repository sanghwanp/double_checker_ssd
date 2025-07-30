#include <iostream>
#include <sstream>

#include "../Shell/CmdRead.h"
#include "../Shell/MockSSD.h"
#include "gmock/gmock.h"

TEST(CommandTest, ReadDefault) {
  std::ostringstream oss;
  auto oldCoutStreamBuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  MockSSD ssd;
  CommandRead cmd(&ssd);

  EXPECT_TRUE(cmd.Call({"read", "1"}));
 
  std::cout.rdbuf(oldCoutStreamBuf);
  std::string outputStr = oss.str();

  EXPECT_EQ("[Read] LBA 1 : 0x00000000\n", outputStr);
}

TEST(CommandTest, ReadValue) {
  std::ostringstream oss;
  auto oldCoutStreamBuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  MockSSD ssd;
  CommandRead cmd(&ssd);
  ssd.Write(1, "0x12345678");

  EXPECT_TRUE(cmd.Call({"read", "1"}));

  std::cout.rdbuf(oldCoutStreamBuf);
  std::string outputStr = oss.str();

  EXPECT_EQ("[Read] LBA 1 : 0x12345678\n", outputStr);
}

TEST(CommandTest, ReadInvalidLBA) {
  MockSSD ssd;
  CommandRead cmd(&ssd);

  EXPECT_FALSE(cmd.Call({"read", "-1"}));
}
