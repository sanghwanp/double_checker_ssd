#include <iostream>
#include <sstream>

#include "../Shell/CmdFlush.h"
#include "../Shell/MockSSD.h"
#include "../Shell/Parser.h"
#include "gTestCommandCallCommon.h"
#include "gmock/gmock.h"

using namespace testing;

class MockableMockSSD : public MockSSD {
 public:
  MOCK_METHOD(void, Flush, (), (override));
};

class FlushTest : public CommandCallCommon {
 protected:
  MockableMockSSD ssd;
  CommandFlush cmd{&ssd};
};

TEST_F(FlushTest, FlushDefault_CallsFlushOnce) {
  EXPECT_CALL(ssd, Flush()).Times(1);
  EXPECT_TRUE(cmd.Call(GenParam("flush")));
}

TEST_F(FlushTest, FlushBadArgs_NoFlush) {
  EXPECT_CALL(ssd, Flush()).Times(0);
  EXPECT_FALSE(cmd.Call(GenParam("flush now")));
}
