#include <iostream>
#include <vector>

#include "../SSD/CommandBufferConfig.h"
#include "../SSD/CommandBufferEntry.h"
#include "../SSD/CommandBufferHandler.h"
#include "../SSD/CommandBufferOptimizer.h"
#include "gmock/gmock.h"

using namespace testing;
using std::vector;
using CmdType = CommandBufferConfig::CmdType;

struct OptimizeTestCase {
  vector<CommandBufferEntry> input;
  size_t expected_size;
};

class CmdBufferParamTestFixture : public TestWithParam<OptimizeTestCase> {
 public:
  CommandBufferOptimizer cmdBufferOptimizer;
};

namespace {  // input인 cmds vector가 valid한지 Test
void ExpectWriteHasData(const vector<CommandBufferEntry>& cmds) {
  for (const auto& cmd : cmds) {
    if (cmd.data != 0) {
      EXPECT_EQ(cmd.cmdType, CmdType::WRITE);
    }
  }
}

void ExpectWriteIsLengthOne(const vector<CommandBufferEntry>& cmds) {
  for (const auto& cmd : cmds) {
    if (cmd.cmdType == CmdType::WRITE) {
      EXPECT_EQ(cmd.startLba, cmd.endLba);
    }
  }
}

void ExpectEraseHasZeroData(const vector<CommandBufferEntry>& cmds) {
  for (const auto& cmd : cmds) {
    if (cmd.cmdType == CmdType::ERASE) {
      EXPECT_EQ(cmd.data, 0);
    }
  }
}

void ExpectSizeAtMost(const vector<CommandBufferEntry>& cmds, size_t max) {
  EXPECT_LE(cmds.size(), max);
}
}  // namespace

TEST_P(CmdBufferParamTestFixture, CmdTypeIsWriteWhenDataIsNotZero) {
  ExpectWriteHasData(GetParam().input);
}

TEST_P(CmdBufferParamTestFixture, LengthIsOneWhenCmdTypeIsWrite) {
  ExpectWriteIsLengthOne(GetParam().input);
}

TEST_P(CmdBufferParamTestFixture, DataIsZeroWhenCmdTypeIsErase) {
  ExpectEraseHasZeroData(GetParam().input);
}

TEST_P(CmdBufferParamTestFixture, CmdsVectorSizeLessThanEqual5) {
  ExpectSizeAtMost(GetParam().input, 5);
}

TEST_P(CmdBufferParamTestFixture, OptimizeResultMatchesExpectedSize) {
  const auto& tc = GetParam();
  std::cout << "Input:\n";
  for (const auto& cmd : tc.input) cmd.Print();

  std::cout << "\nOutput:\n";
  vector<CommandBufferEntry> result = cmdBufferOptimizer.Optimize(tc.input);
  for (const auto& intv : result) intv.Print();

  EXPECT_EQ(result.size(), tc.expected_size);
}

INSTANTIATE_TEST_SUITE_P(CmdTestCases, CmdBufferParamTestFixture,
                         Values(OptimizeTestCase{{{CmdType::ERASE, 1, 10, 0},
                                                  {CmdType::WRITE, 9, 9, 2},
                                                  {CmdType::WRITE, 7, 7, 2},
                                                  {CmdType::WRITE, 8, 8, 1},
                                                  {CmdType::ERASE, 4, 6, 0}},
                                                 4},
                                OptimizeTestCase{{{CmdType::WRITE, 20, 20, 1},
                                                  {CmdType::WRITE, 21, 21, 2},
                                                  {CmdType::WRITE, 20, 20, 3}},
                                                 2},
                                OptimizeTestCase{{{CmdType::WRITE, 1, 1, 1},
                                                  {CmdType::WRITE, 1, 1, 1}},
                                                 1}));

class CmdBufferHandlerFixture : public Test {
 public:
  CommandBufferHandler cmdBufferHandler;

  void SetUp() override { cmdBufferHandler.Flush(); }
};

TEST_F(CmdBufferHandlerFixture, EraseThenReadReturnsZero) {
  cmdBufferHandler.AddErase(1, 10);
  unsigned int value = 0;

  EXPECT_FALSE(cmdBufferHandler.TryFastRead(0, value));
  EXPECT_EQ(value, CommandBufferConfig::NOT_AVAILABLE);

  EXPECT_TRUE(cmdBufferHandler.TryFastRead(1, value));
  EXPECT_EQ(value, 0);
}

TEST_F(CmdBufferHandlerFixture, WriteThenReadReturnsWrittenValue) {
  cmdBufferHandler.AddWrite(1, 10);
  unsigned int value = 0;

  EXPECT_FALSE(cmdBufferHandler.TryFastRead(0, value));
  EXPECT_EQ(value, CommandBufferConfig::NOT_AVAILABLE);

  EXPECT_TRUE(cmdBufferHandler.TryFastRead(1, value));
  EXPECT_EQ(value, 10);
}

TEST_F(CmdBufferHandlerFixture, WriteOverflowTriggersFlushAndUpdate) {
  cmdBufferHandler.Flush();
  cmdBufferHandler.AddWrite(1, 10);
  cmdBufferHandler.AddWrite(2, 11);
  cmdBufferHandler.AddWrite(3, 12);
  cmdBufferHandler.AddWrite(4, 13);
  cmdBufferHandler.AddWrite(5, 14);

  unsigned int value = 0;
  EXPECT_FALSE(cmdBufferHandler.TryFastRead(0, value));
  EXPECT_EQ(value, CommandBufferConfig::NOT_AVAILABLE);

  EXPECT_TRUE(cmdBufferHandler.TryFastRead(1, value));
  EXPECT_EQ(value, 10);

  std::vector<CommandBufferEntry> flushed = cmdBufferHandler.AddWrite(1, 20);
  for (const auto& cmd : flushed) {
    std::cout << cmd.ToString() << "\n";
  }

  EXPECT_TRUE(cmdBufferHandler.TryFastRead(1, value));
  EXPECT_EQ(value, 20);
}
