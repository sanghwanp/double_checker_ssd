#include "../Shell/MockSSD.h"
#include "../Shell/TestScriptCase1.h"
#include "gmock/gmock.h"

using namespace testing;

class MockTestScriptCase1 : public TestScriptCase1 {
 public:
  MockTestScriptCase1(SSDInterface* ssdinterface)
      : TestScriptCase1(ssdinterface) {}
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
  MockTestScriptCase1 mockTestScriptCase1{&ssdDriver};
  TestScriptCase1 realTestScriptCase1{&ssdDriver};
};

TEST_F(TestScriptCaseFixture, mockExec) {
  EXPECT_CALL(mockTestScriptCase1, Call())
      .WillOnce(DoAll(InvokeWithoutArgs([&] {
                        std::cout << mockTestScriptCase1.TEST_SCRIPT_PASS_OUTPUT
                                  << std::endl;
                      }),
                      Return(true)));
  bool ret = mockTestScriptCase1.Call();
  EXPECT_TRUE(ret);
  EXPECT_THAT(oss.str(),
              AllOf(HasSubstr(mockTestScriptCase1.TEST_SCRIPT_PASS_OUTPUT),
            Not(HasSubstr(mockTestScriptCase1.TEST_SCRIPT_FAIL_OUTPUT))));
}

TEST_F(TestScriptCaseFixture, realExec) {
  bool ret = realTestScriptCase1.Call();
  EXPECT_TRUE(ret);
  EXPECT_THAT(oss.str(),
              AllOf(HasSubstr(realTestScriptCase1.TEST_SCRIPT_PASS_OUTPUT),
            Not(HasSubstr(realTestScriptCase1.TEST_SCRIPT_FAIL_OUTPUT))));
}
