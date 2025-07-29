#include <iostream>

#include "gmock/gmock.h"
using namespace testing;
using namespace std;

class WriteTestFixture : public Test {
public:
};

TEST_F(WriteTestFixture, 01_Parse_Write_Cmd) { 
	EXPECT_EQ(1, 1); 
}