#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../Shell/MockSSD.h"
#include "../Shell/ScriptRunner.h"

using namespace testing;

class ScriptRunnerFileTest : public ::testing::Test {
 protected:
  const char* kScriptFile = "temp_script.txt";
  std::ostringstream out;
  std::streambuf* oldCout = nullptr;

  void SetUp() override { oldCout = std::cout.rdbuf(out.rdbuf()); }

  void TearDown() override {
    std::cout.rdbuf(oldCout);
    std::remove(kScriptFile);
  }
};

// 1) 파일 없을 때 에러 메시지
TEST_F(ScriptRunnerFileTest, NonexistentFile_ShowsError) {
  MockSSD ssd;
  ScriptRunner runner(&ssd, "no_such_file.txt");

  runner.run();

  std::string o = out.str();
  EXPECT_NE(o.find("Cannot open script file: no_such_file.txt"),
            std::string::npos);
}

// 2) 알 수 없는 스크립트 한 줄
TEST_F(ScriptRunnerFileTest, UnknownScript_PrintsInvalidAndStops) {
  {
    std::ofstream f(kScriptFile);
    f << "foobar\n";
  }

  MockSSD ssd;
  ScriptRunner runner(&ssd, kScriptFile);
  runner.run();

  EXPECT_EQ("foobar --- Run...INVALID SCRIPT\n", out.str());
}

// 3) 단일 유효 스크립트 (long 이름)
TEST_F(ScriptRunnerFileTest, SingleKnownLong_PrintsRunPass) {
  {
    std::ofstream f(kScriptFile);
    f << "1_FullWriteAndReadCompare\n";
  }

  MockSSD ssd;
  ScriptRunner runner(&ssd, kScriptFile);
  runner.run();

  std::string o = out.str();
  EXPECT_NE(o.find("1_FullWriteAndReadCompare --- Run...Pass\n"),
            std::string::npos);
}

// 4) 단일 유효 스크립트 (short 이름)
TEST_F(ScriptRunnerFileTest, SingleKnownShort_PrintsRunPass) {
  {
    std::ofstream f(kScriptFile);
    f << "1_\n";
  }

  MockSSD ssd;
  ScriptRunner runner(&ssd, kScriptFile);
  runner.run();

  std::string o = out.str();
  EXPECT_NE(o.find("1_ --- Run...Pass\n"), std::string::npos);
}

// 5) 여러 스크립트: 정상 둘 → 잘못된 셋째 → 넷째는 실행 안 함
TEST_F(ScriptRunnerFileTest, MultipleScripts_StopOnInvalid) {
  {
    std::ofstream f(kScriptFile);
    f << "1_\n";
    f << "2_\n";
    f << "BAD_SCRIPT\n";
    f << "3_\n";
  }

  MockSSD ssd;
  ScriptRunner runner(&ssd, kScriptFile);
  runner.run();

  std::string o = out.str();
  EXPECT_NE(o.find("1_ --- Run...Pass\n"), std::string::npos);
  EXPECT_NE(o.find("2_ --- Run...Pass\n"), std::string::npos);
  EXPECT_NE(o.find("BAD_SCRIPT --- Run...INVALID SCRIPT\n"), std::string::npos);
  EXPECT_EQ(o.find("3_ --- Run..."), std::string::npos);
}
