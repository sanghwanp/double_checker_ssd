#include <vector>

#include "CmdBuffer.h"
#include "Interval.h"
#include "gmock/gmock.h"

using namespace testing;
using std::vector;

struct OptimizeTestCase {
  vector<Interval> input;
  size_t expected_size;
};

class CmdBufferParamTestFixture : public TestWithParam<OptimizeTestCase> {
 public:
  CmdBuffer cmdBuffer;
};

INSTANTIATE_TEST_SUITE_P(
    CmdTestCases, CmdBufferParamTestFixture,
    Values(OptimizeTestCase{{{1, 10, 0, CmdType::ERASE},  // input: cmds[0]
                             {9, 9, 2, CmdType::WRITE},
                             {7, 7, 2, CmdType::WRITE},
                             {8, 8, 1, CmdType::WRITE},
                             {4, 6, 0, CmdType::ERASE}},
                            4},  // expected_size
           OptimizeTestCase{
               {{1, 10, 0, CmdType::ERASE},
                {9, 9, 2, CmdType::WRITE},
                {7, 7, 2, CmdType::WRITE},
                {8, 8, 1, CmdType::WRITE},
                {4, 6, 0, CmdType::ERASE}},
               4  // ← 다른 기대값
           }));

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
      EXPECT_EQ(cmd.s, cmd.e);
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
  vector<Interval> result = cmdBuffer.Optimize(tc.input);
  for (const auto& intv : result) intv.Print();

  EXPECT_EQ(result.size(), tc.expected_size);
}
