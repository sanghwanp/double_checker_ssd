#include <iostream>
#include <vector>

#include "../SSD/CommandBufferConfig.h"
#include "../SSD/CommandBufferEntry.h"
#include "../SSD/CommandBufferHandler.h"
#include "../SSD/CommandBufferOptimizer.h"
#include "../SSD/Types.h"
#include "gmock/gmock.h"

#define DEBUG_PRINT

using namespace testing;
using std::vector;

class CmdBufferHandlerTestFixture : public Test {
 protected:
  CommandBufferHandler handler;

  void SetUp() override { handler.Flush(); }

  void ExpectTryFastReadFail(unsigned int lba) {
    unsigned int value;
    bool isSucc = handler.TryFastRead(lba, value);
    EXPECT_EQ(isSucc, false);
    EXPECT_EQ(value, NOT_AVAILABLE);
  }

  void ExpectTryFastReadSucc(unsigned int lba, unsigned int expectedValue) {
    unsigned int value;
    bool isSucc = handler.TryFastRead(lba, value);
    EXPECT_EQ(isSucc, true);
    EXPECT_EQ(value, expectedValue);
  }

  static const int NOT_AVAILABLE = CommandBufferConfig::NOT_AVAILABLE;
  static const int MIN_LBA = CommandBufferConfig::MIN_LBA;
  static const int MAX_LBA = CommandBufferConfig::MAX_LBA;
  static const int MAX_LBA_CNT = CommandBufferConfig::MAX_LBA_CNT;
  static const int LBA_ERASE_RANGE_LIMIT =
      CommandBufferConfig::LBA_ERASE_RANGE_LIMIT;
  static const int MAX_BUFFER = CommandBufferConfig::MAX_BUFFER;

  bool IsBufferFlushed(int addOperationCount) const {
    return addOperationCount > MAX_BUFFER && (addOperationCount % 5) == 1;
  }
};

#if 1  // Write
TEST_F(CmdBufferHandlerTestFixture, TC08_Write_BasicOperation) {
  int addOperationCount = 0;
  for (int lba = MIN_LBA, data = 1; lba <= MAX_LBA; lba++, data++) {
    auto cmds = handler.AddWrite(lba, data);
    ++addOperationCount;

    if (!IsBufferFlushed(addOperationCount)) {
      EXPECT_EQ(cmds.size(), 0);
      continue;
    }

    EXPECT_EQ(cmds.size(), 5);

    sort(cmds.begin(), cmds.end(),
         [&](const CommandBufferEntry &lhs, const CommandBufferEntry &rhs)
             -> bool { return lhs.startLba < rhs.startLba; });

    const int EXPECTED_LBA[] = {lba - 5, lba - 4, lba - 3, lba - 2, lba - 1};
    const int EXPECTED_DATA[] = {data - 5, data - 4, data - 3, data - 2,
                                 data - 1};
    for (int i = 0; i < cmds.size(); i++) {
      EXPECT_EQ(cmds[i].startLba, EXPECTED_LBA[i]);
      EXPECT_EQ(cmds[i].endLba, EXPECTED_LBA[i]);
      EXPECT_EQ(cmds[i].data, EXPECTED_DATA[i]);
    }
  }
}
#endif

#if 1  // Erase
TEST_F(CmdBufferHandlerTestFixture, TC06_ExceedLbaWhenErase_ThrowException) {
  EXPECT_NO_THROW({ handler.AddErase(MIN_LBA, -1); });
  EXPECT_THROW({ handler.AddErase(MIN_LBA, -2); }, std::invalid_argument);

  EXPECT_NO_THROW({ handler.AddErase(MAX_LBA, 1); });
  EXPECT_THROW({ handler.AddErase(MAX_LBA, 2); }, std::invalid_argument);
}

TEST_F(CmdBufferHandlerTestFixture,
       TC07_ExceedLbaEraseRangeLimit_ThrowException) {
  EXPECT_NO_THROW({ handler.AddErase(MIN_LBA, LBA_ERASE_RANGE_LIMIT); });
  EXPECT_THROW(
      { handler.AddErase(MIN_LBA, LBA_ERASE_RANGE_LIMIT + 1); },
      std::invalid_argument);

  EXPECT_NO_THROW(
      { handler.AddErase(LBA_ERASE_RANGE_LIMIT, -LBA_ERASE_RANGE_LIMIT); });
  EXPECT_THROW(
      { handler.AddErase(LBA_ERASE_RANGE_LIMIT, -LBA_ERASE_RANGE_LIMIT - 1); },
      std::invalid_argument);
}

TEST_F(CmdBufferHandlerTestFixture, TC08_EraseInvalidDelta_ThrowException) {
  EXPECT_THROW({ handler.AddErase(1, 0); }, std::invalid_argument);
}

TEST_F(CmdBufferHandlerTestFixture, TC08_Erase_BasicOperation) {
  int addOperationCount = 0;
  int addOperationCountLimit = 42;
  for (int lba = MIN_LBA, data = 1; addOperationCount < addOperationCountLimit;
       lba++, data++) {
    auto cmds = handler.AddErase(lba, 1);
    ++addOperationCount;

    if (addOperationCount != addOperationCountLimit) {
      EXPECT_EQ(cmds.size(), 0);
      continue;
    }

    EXPECT_EQ(cmds.size(), 5);

    sort(cmds.begin(), cmds.end(),
         [&](const CommandBufferEntry &lhs, const CommandBufferEntry &rhs)
             -> bool { return lhs.startLba < rhs.startLba; });

    const int EXPECTED_START_LBA[] = {MIN_LBA,
                                      MIN_LBA + 1 * LBA_ERASE_RANGE_LIMIT,
                                      MIN_LBA + 2 * LBA_ERASE_RANGE_LIMIT,
                                      MIN_LBA + 3 * LBA_ERASE_RANGE_LIMIT,
                                      MIN_LBA + 4 * LBA_ERASE_RANGE_LIMIT};
    const int EXPECTED_END_LBA[] = {MIN_LBA + 1 * LBA_ERASE_RANGE_LIMIT - 1,
                                    MIN_LBA + 2 * LBA_ERASE_RANGE_LIMIT - 1,
                                    MIN_LBA + 3 * LBA_ERASE_RANGE_LIMIT - 1,
                                    MIN_LBA + 4 * LBA_ERASE_RANGE_LIMIT - 1,
                                    MIN_LBA + 4 * LBA_ERASE_RANGE_LIMIT};
    for (int i = 0; i < cmds.size(); i++) {
      EXPECT_EQ(cmds[i].startLba, EXPECTED_START_LBA[i]);
      EXPECT_EQ(cmds[i].endLba, EXPECTED_END_LBA[i]);
      EXPECT_EQ(cmds[i].data, 0);
    }
  }
}
#endif

#if 1  // Flush
// TC03: Write 버퍼가 가득 차면 flush 발생 및 최신값 갱신됨
TEST_F(CmdBufferHandlerTestFixture, TC03_WriteBufferOverflow_FlushTriggered) {
  const int SIZE = 5;
  const int LBAS[SIZE] = {1, 2, 3, 4, 5};
  const int DATA[SIZE] = {11, 12, 13, 14, 15};

  for (int i = 0; i < SIZE; i++) {
    handler.AddWrite(LBAS[i], DATA[i]);
  }

  const int FIRST_LBA = LBAS[0];
  const int LAST_LBA = LBAS[SIZE - 1];

  ExpectTryFastReadFail(FIRST_LBA - 1);
  for (int i = 0; i < SIZE; i++) {
    ExpectTryFastReadSucc(LBAS[i], DATA[i]);
  }
  ExpectTryFastReadFail(LAST_LBA + 1);

  const int OLD_LBA = FIRST_LBA;
  const int NEW_DATA = DATA[SIZE - 1] + 0x12345;  // 11~15가 아닌 아무 값
  auto flushed_cmds = handler.AddWrite(OLD_LBA, NEW_DATA);
#ifdef DEBUG_PRINT
  for (const auto &cmd : flushed_cmds) {
    std::cout << cmd.ToString() << "\n";
  }
#endif

  EXPECT_EQ(flushed_cmds.size(), SIZE);

  ExpectTryFastReadFail(0);
  ExpectTryFastReadSucc(OLD_LBA, NEW_DATA);
  for (int i = 1; i < SIZE; i++) {
    ExpectTryFastReadFail(LBAS[i]);
  }
  ExpectTryFastReadFail(6);
}
#endif

#if 1  // TryFastRead
TEST_F(CmdBufferHandlerTestFixture, TC00_NeverUsedBuffer_ReadReturnsZero) {
  for (int lba = 0; lba < MAX_LBA_CNT; lba++) {
    ExpectTryFastReadFail(lba);
  }
}

// TC01: Erase된 영역은 0으로 읽혀야 함
TEST_F(CmdBufferHandlerTestFixture, TC01_EraseRange_ReadReturnsZero) {
  const int START_LBA = 1, END_LBA = 10;
  handler.AddErase(START_LBA, END_LBA);

  const int erasedValue = 0;
  ExpectTryFastReadFail(START_LBA - 1);
  for (int lba = START_LBA; lba <= END_LBA; lba++) {
    ExpectTryFastReadSucc(lba, erasedValue);
  }
  ExpectTryFastReadFail(END_LBA + 1);
}

// TC02: Write 후에는 해당 LBA를 정확히 읽을 수 있어야 함
TEST_F(CmdBufferHandlerTestFixture, TC02_WriteThenRead_ReturnsValue) {
  const int LBA = 1, DATA = 10;
  handler.AddWrite(LBA, DATA);

  ExpectTryFastReadFail(LBA - 1);
  ExpectTryFastReadSucc(LBA, DATA);
  ExpectTryFastReadFail(LBA + 1);
}
#endif

#if 1  // Optimize
TEST_F(CmdBufferHandlerTestFixture, TC04_Optimize_ReducesCommandCount) {
  handler.AddErase(1, 10);
  handler.AddWrite(9, 2);
  handler.AddWrite(7, 2);
  handler.AddWrite(8, 1);
  handler.AddErase(4, 2);

  auto cmds = handler.Flush();
  EXPECT_EQ(cmds.size(), 4);
}

TEST_F(CmdBufferHandlerTestFixture, TC05_Optimize_OverwriteSameData) {
  handler.AddWrite(1, 0x10);
  handler.AddWrite(1, 0x10);
  handler.AddWrite(1, 0x10);
  handler.AddWrite(1, 0x10);
  handler.AddWrite(1, 0x10);

  auto cmds = handler.Flush();
  EXPECT_EQ(cmds.size(), 1);
  EXPECT_EQ(cmds[0].data, 0x10);
}

TEST_F(CmdBufferHandlerTestFixture, TC05_Optimize_OverwriteDiffData) {
  handler.AddWrite(1, 1);
  handler.AddWrite(1, 2);
  handler.AddWrite(1, 3);
  handler.AddWrite(1, 4);
  handler.AddWrite(1, 5);

  auto cmds = handler.Flush();
  EXPECT_EQ(cmds.size(), 1);
  EXPECT_EQ(cmds[0].data, 5);
}

TEST_F(CmdBufferHandlerTestFixture, TC06_Optimize_Overwrite2) {
  handler.AddWrite(20, 1);
  handler.AddWrite(21, 2);
  handler.AddWrite(20, 3);

  auto cmds = handler.Flush();
  EXPECT_EQ(cmds.size(), 2);
}

TEST_F(CmdBufferHandlerTestFixture, TC10_Optimize_Case1) {
  handler.AddWrite(5, 1);
  handler.AddWrite(4, 1);
  handler.AddWrite(7, 1);
  handler.AddErase(5, 3);
  handler.AddWrite(6, 1);

  auto cmds = handler.Flush();
  EXPECT_EQ(cmds.size(), 3);
}

TEST_F(CmdBufferHandlerTestFixture, TC11_Optimize_Case2) {
  handler.AddErase(0, 10);
  handler.AddErase(3, 5);
  handler.AddErase(15, 10);
  handler.AddErase(6, 8);
  handler.AddErase(13, 5);

  auto cmds = handler.Flush();
  EXPECT_EQ(cmds.size(), 3);
}

TEST_F(CmdBufferHandlerTestFixture, TC12_NotOptimize_Case3) {
  handler.AddWrite(50, 50);
  handler.AddErase(51, 1);

  auto cmds = handler.Flush();
  EXPECT_EQ(cmds.size(), 2);
}

TEST_F(CmdBufferHandlerTestFixture, TC13_Optimize_Case4) {
  handler.AddWrite(50, 50);
  handler.AddErase(51, 1);
  handler.AddWrite(52, 50);
  handler.AddErase(53, 1);
  handler.AddErase(49, 1);

  auto cmds = handler.Flush();
  EXPECT_EQ(cmds.size(), 3);
}

TEST_F(CmdBufferHandlerTestFixture, TC14_Optimize_Case5) {
  handler.AddWrite(50, 50);
  handler.AddErase(51, 1);
  handler.AddWrite(50, 52);
  handler.AddErase(52, 1);
  handler.AddErase(49, 1);

  auto cmds = handler.Flush();
  EXPECT_EQ(cmds.size(), 2);
}

TEST_F(CmdBufferHandlerTestFixture, TC15_Optimize_Case6) {
  handler.AddWrite(50, 50);
  handler.AddErase(51, 1);
  handler.AddWrite(50, 52);
  handler.AddWrite(51, 2);
  handler.AddErase(51, 1);

  auto cmds = handler.Flush();
  EXPECT_EQ(cmds.size(), 2);
}
#endif

#if 1  // Etc. - code coverage를 채우기 위한 Test
TEST(CommandBufferEntry, TC16_ForCodeCoverage) {
  EXPECT_THROW(
      { CommandBufferEntry cmd(CMD_TYPE::eWriteCmd, 1, 2, 1); },
      std::invalid_argument);

  EXPECT_THROW(
      { CommandBufferEntry cmd(CMD_TYPE::eEraseCmd, 1, 2, 1); },
      std::invalid_argument);

  EXPECT_THROW(
      { CommandBufferEntry cmd(CMD_TYPE::eFlushCmd, 1, 2, 1); },
      std::invalid_argument);

  EXPECT_THROW(
      { CommandBufferEntry cmd(CMD_TYPE::eReadCmd, 1, 2, 1); },
      std::invalid_argument);

  EXPECT_THROW(
      { CommandBufferEntry cmd(CMD_TYPE::eInvalidCmd, 1, 2, 1); },
      std::invalid_argument);

  CommandBufferEntry cmd(CMD_TYPE::eWriteCmd, 1, 1, 1);
  cmd.cmdType = eInvalidCmd;
  EXPECT_THROW({ cmd.ToString(); }, std::invalid_argument);
}
#endif
