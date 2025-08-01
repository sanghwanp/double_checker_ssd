#include "../Shell/ITestScriptCase.h"
#include "../Shell/MockSSD.h"
#include "../Shell/TestScriptCase1.h"
#include "../Shell/TestScriptCase2.h"
#include "../Shell/TestScriptCase3.h"
#include "gmock/gmock.h"

using namespace testing;

class MockTestScriptCase : public ITestScriptCase {
 public:
  MockTestScriptCase(SSDInterface* ssdinterface)
      : ITestScriptCase(ssdinterface, 0, "mock") {}
  MOCK_METHOD(bool, Call, (), (override));
};

class TestScriptCaseFixture : public Test {
 public:
  void SetUp() override {
    backupOutBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
  }

  void TearDown() override { std::cout.rdbuf(backupOutBuf); }

  std::ostringstream oss;
  std::streambuf* backupOutBuf;

  MockSSD ssdDriver;
  MockTestScriptCase mockTestScriptCase{&ssdDriver};
  TestScriptCase1 realTestScriptCase1{&ssdDriver};
  TestScriptCase2 realTestScriptCase2{&ssdDriver};
  TestScriptCase3 realTestScriptCase3{&ssdDriver};
};

TEST_F(TestScriptCaseFixture, mockExec) {
  EXPECT_CALL(mockTestScriptCase, Call())
      .WillOnce(DoAll(InvokeWithoutArgs([&] {
                        std::cout << ITestScriptCase::TEST_SCRIPT_PASS_OUTPUT
                                  << std::endl;
                      }),
                      Return(true)));
  bool ret = mockTestScriptCase.Call();
  EXPECT_TRUE(ret);
  EXPECT_THAT(
      oss.str(),
      AllOf(HasSubstr(ITestScriptCase::TEST_SCRIPT_PASS_OUTPUT),
                    Not(HasSubstr(ITestScriptCase::TEST_SCRIPT_FAIL_OUTPUT))));
}

TEST_F(TestScriptCaseFixture, testScriptCase1Exec) {
  bool ret = realTestScriptCase1.Call();
  EXPECT_TRUE(ret);
}

TEST_F(TestScriptCaseFixture, testScriptCase2Exec) {
  bool ret = realTestScriptCase2.Call();
  EXPECT_TRUE(ret);
}

TEST_F(TestScriptCaseFixture, testScriptCase3Exec) {
  bool ret = realTestScriptCase3.Call();
  EXPECT_TRUE(ret);
}
