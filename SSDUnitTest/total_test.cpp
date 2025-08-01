#include <gtest/gtest.h>
#include "../SSD/SSD.h"
#include "../SSD/FileDriver.h"

class SSDTest : public ::testing::Test {
public:
    SSDTest() : ssd(SSD::GetInstance()), fileDriver(FileDriver::GetInstance()) {}
    unsigned int GetCachedData(unsigned int lba) {
        return *fileDriver.GetBufferData(lba);
    }
    std::string readOutputFile() {
        std::ifstream file(READ_OUTPUT_FILE_NAME);
        std::string content((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
        return content;
    }
protected:
    SSD ssd;
    FileDriver& fileDriver;
    const unsigned int TEST_LBA = 5;
    const unsigned int TEST_DATA = 0x12345678;
    const std::string WRITE_CMD = "W 5 0x12345678";
    const std::string READ_CMD = "R 5";
    const std::string READ_OUTPUT_FILE_NAME = "output.txt";
};

TEST_F(SSDTest, WriteAndRead_CachedData) {
    // Write
    std::vector<std::string> writeArgs = { "W", "5", "0x12345678" };
    ssd.Run(writeArgs);

    // Read
    std::vector<std::string> readArgs = { "R", "5" };
    ssd.Run(readArgs);

    // Check cache
    unsigned int cached = GetCachedData(TEST_LBA);
    EXPECT_EQ(cached, TEST_DATA);
}

TEST_F(SSDTest, ReadCommand_InvalidLBA) {

    // Read
    std::vector<std::string> readArgs = { "R", "140" };
    ssd.Run(readArgs);

    string output = readOutputFile();

    EXPECT_EQ(output, "ERROR\n");
}

TEST_F(SSDTest, Run_InvalidCommandType) {
    std::vector<std::string> invalidArgs = { "invalid", "5", "0x12345678" };
    // 정상적으로 처리하지 못하면 내부적으로 "Invalid command" 출력
    // 예외는 발생하지 않으나, 캐시에는 변화 없음
    unsigned int before = GetCachedData(TEST_LBA);
    ssd.Run(invalidArgs);
    unsigned int after = GetCachedData(TEST_LBA);
    EXPECT_EQ(before, after);
}
