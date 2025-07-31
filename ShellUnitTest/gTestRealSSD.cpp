#include <cstdio>
#include <fstream>

#include "../Shell/RealSSD.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

class MockRealSSD : public RealSSD {
 public:
  using RealSSD::RealSSD;  
  MOCK_METHOD(int, execCommand, (const std::string& cmd), (override));
};

class RealSSDTest : public Test {
 protected:
  const std::string exe = "ssd.exe";
  const std::string outFile = "ssd_output.txt";

  MockRealSSD ssd{exe, outFile};

  void writeOutput(const std::string& v) {
    std::ofstream o(outFile, std::ios::trunc);
    o << v;
  }

  void TearDown() override { std::remove(outFile.c_str()); }
};

// 1) Write: execCommand 호출 여부 검증
TEST_F(RealSSDTest, Write_ExecutesCorrectCommand) {
  EXPECT_CALL(ssd, execCommand(exe + " W 42 0xCAFEBABE")).WillOnce(Return(0));
  ssd.Write(42, "0xCAFEBABE");
}

// 2) Read 정상: 파일에 값 써두고 Read → 반환값 검증
TEST_F(RealSSDTest, Read_ReturnsWrittenOutput) {
  EXPECT_CALL(ssd, execCommand(exe + " R 7")).WillOnce(Return(0));
  writeOutput("0xDEADBEEF");
  auto v = ssd.Read(7);
  EXPECT_EQ(v, "0xDEADBEEF");
}

// 3) Read 실패(파일 없음): 삭제된 상태에서 Read → "ERROR" 반환
TEST_F(RealSSDTest, Read_MissingFile_ReturnsError) {
  EXPECT_CALL(ssd, execCommand(exe + " R 3")).WillOnce(Return(0));
  std::remove(outFile.c_str());
  auto v = ssd.Read(3);
  EXPECT_EQ(v, "ERROR");
}

// 4) Read 실패(빈 파일): 빈 파일 만들어 놓고 Read → "ERROR" 반환
TEST_F(RealSSDTest, Read_EmptyFile_ReturnsError) {
  EXPECT_CALL(ssd, execCommand(exe + " R 5")).WillOnce(Return(0));
  std::ofstream o(outFile, std::ios::trunc);
  o.close();
  auto v = ssd.Read(5);
  EXPECT_EQ(v, "ERROR");
}