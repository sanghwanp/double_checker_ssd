#include <vector>

#include "../SSD/CommandBufferConfig.h"
#include "../SSD/CommandBufferEntry.h"
#include "../SSD/CommandBufferOptimizer.h"
#include "../SSD/CommandBufferHandler.h"
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

// 공통 검증: data != 0이면 WRITE여야 함
TEST_P(CmdBufferParamTestFixture, CmdTypeIsWriteWhenDataIsNotZero) {
  const auto& tc = GetParam();
  for (const auto& cmd : tc.input) {
    if (cmd.data != 0) {
      EXPECT_EQ(cmd.cmdType, CmdType::WRITE);
    }
  }
}

// 공통 검증: WRITE이면 s == e 이어야 함
TEST_P(CmdBufferParamTestFixture, LengthIsOneWhenCmdTypeIsWrite) {
  const auto& tc = GetParam();
  for (const auto& cmd : tc.input) {
    if (cmd.cmdType == CmdType::WRITE) {
      EXPECT_EQ(cmd.startLba, cmd.endLba);
    }
  }
}

// 공통 검증: ERASE이면 data == 0 이어야 함
TEST_P(CmdBufferParamTestFixture, DataIsZeroWhenCmdTypeIsErase) {
  const auto& tc = GetParam();
  for (const auto& cmd : tc.input) {
    if (cmd.cmdType == CmdType::ERASE) {
      EXPECT_EQ(cmd.data, 0);
    }
  }
}

// 공통 검증: cmds 길이는 5 이하
TEST_P(CmdBufferParamTestFixture, CmdsVectorSizeLessThanEqual5) {
  const auto& tc = GetParam();
  EXPECT_LE(tc.input.size(), 5);
}

// 최적화 결과 확인(예시)
TEST_P(CmdBufferParamTestFixture, OptimizeResultMatchesExpectedSize) {
  const auto& tc = GetParam();

  puts("Input:");
  for (const auto& cmd : tc.input) cmd.Print();

  puts("Output:");
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

class CmdBufferHandlerFixture : public Test{
public:
  CommandBufferHandler cmdBufferHandler;

  void SetUp() {
      cmdBufferHandler.Flush();
  }
};

TEST_F(CmdBufferHandlerFixture, TC06_E1_10_FR0FR1) {
  cmdBufferHandler.AddErase(1, 10);
  unsigned int value = 0;
  EXPECT_EQ(cmdBufferHandler.TryFastRead(0, value), false);
  EXPECT_EQ(value, CommandBufferConfig::NOT_AVAILABLE);

  EXPECT_EQ(cmdBufferHandler.TryFastRead(1, value), true);
  EXPECT_EQ(value, 0);
}

TEST_F(CmdBufferHandlerFixture, TC07_W1_10_FR0FR1) {
  cmdBufferHandler.AddWrite(1, 10);
  unsigned int value = 0;
  EXPECT_EQ(cmdBufferHandler.TryFastRead(0, value), false);
  EXPECT_EQ(value, CommandBufferConfig::NOT_AVAILABLE);

  EXPECT_EQ(cmdBufferHandler.TryFastRead(1, value), true);
  EXPECT_EQ(value, 10);
}

TEST_F(CmdBufferHandlerFixture, TC08_Write5More_FR0FR1) {
  cmdBufferHandler.Flush();
  cmdBufferHandler.AddWrite(1, 10);
  cmdBufferHandler.AddWrite(2, 11);
  cmdBufferHandler.AddWrite(3, 12);
  cmdBufferHandler.AddWrite(4, 13);
  cmdBufferHandler.AddWrite(5, 14);
  unsigned int value = 0;
  EXPECT_EQ(cmdBufferHandler.TryFastRead(0, value), false);
  EXPECT_EQ(value, CommandBufferConfig::NOT_AVAILABLE);

  EXPECT_EQ(cmdBufferHandler.TryFastRead(1, value), true);
  EXPECT_EQ(value, 10);

  std::vector<CommandBufferEntry> cmds = cmdBufferHandler.AddWrite(1, 20);
  for(int i=0; i<cmds.size(); i++) {
      std::cout << cmds[i].ToString() << "\n";
  }
  EXPECT_EQ(cmdBufferHandler.TryFastRead(1, value), true);
  EXPECT_EQ(value, 20);
}

