#include <iostream>
#include <vector>

#include "../SSD/CommandBufferConfig.h"
#include "../SSD/CommandBufferEntry.h"
#include "../SSD/CommandBufferHandler.h"
#include "../SSD/CommandBufferOptimizer.h"
#include "../SSD/Types.h"
#include "gmock/gmock.h"

using namespace testing;
using std::vector;

class CmdBufferHandlerTestFixture : public Test {
 protected:
  CommandBufferHandler handler;
  const int NOT_AVAILABLE = CommandBufferConfig::NOT_AVAILABLE;

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
};

TEST_F(CmdBufferHandlerTestFixture, TC00_NeverUsedBuffer_ReadReturnsZero) {
    for(int lba=0; lba<CommandBufferConfig::MAX_LBA_CNT; lba++) {
        ExpectTryFastReadFail(lba);
    }
}

// TC01: Erase된 영역은 0으로 읽혀야 함
TEST_F(CmdBufferHandlerTestFixture, TC01_EraseRange_ReadReturnsZero) {
  const int START_LBA = 1, END_LBA = 10;
  handler.AddErase(START_LBA, END_LBA);

  const int erasedValue = 0;
  ExpectTryFastReadFail(START_LBA-1);
  for (int lba = START_LBA; lba <= END_LBA; lba++) {
    ExpectTryFastReadSucc(lba, erasedValue);
  }
  ExpectTryFastReadFail(END_LBA+1);
}

// TC02: Write 후에는 해당 LBA를 정확히 읽을 수 있어야 함
TEST_F(CmdBufferHandlerTestFixture, TC02_WriteThenRead_ReturnsValue) {
  const int LBA = 1, DATA = 10;
  handler.AddWrite(LBA, DATA);

  ExpectTryFastReadFail(LBA-1);
  ExpectTryFastReadSucc(LBA, DATA);
  ExpectTryFastReadFail(LBA+1);
}

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
  const int NEW_DATA = DATA[SIZE - 1] + 5;  // 11~15가 아닌 값
  auto flushed_cmds = handler.AddWrite(OLD_LBA, NEW_DATA);
#ifdef DEBUG_PRINT
  for (const auto& cmd : flushed_cmds) {
    std::cout << cmd.ToString() << "\n";
  }
#endif

  EXPECT_EQ(flushed_cmds.size(), 5);

  ExpectTryFastReadFail(0);
  ExpectTryFastReadSucc(OLD_LBA, NEW_DATA);
  for (int i = 1; i < SIZE; i++) {
    ExpectTryFastReadFail(LBAS[i]);
  }
  ExpectTryFastReadFail(6);
}

TEST_F(CmdBufferHandlerTestFixture, TC04_Optimize_ReducesCommandCount) {
  handler.AddErase(1, 10);
  handler.AddWrite(9, 2);
  handler.AddWrite(7, 2);
  handler.AddWrite(8, 1);
  handler.AddErase(4, 2);

  auto cmds = handler.Flush();
  EXPECT_EQ(cmds.size(), 4);
}

TEST_F(CmdBufferHandlerTestFixture, TC05_Optimize_Overwrite1) {
  handler.AddWrite(1, 1);
  handler.AddWrite(1, 1);

  auto cmds = handler.Flush();
  EXPECT_EQ(cmds.size(), 1);
}

TEST_F(CmdBufferHandlerTestFixture, TC06_Optimize_Overwrite2) {
  handler.AddWrite(20, 1);
  handler.AddWrite(21, 2);
  handler.AddWrite(20, 3);

  auto cmds = handler.Flush();
  EXPECT_EQ(cmds.size(), 2);
}
