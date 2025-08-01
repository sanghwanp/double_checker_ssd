#include <climits>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "ITestScriptCase.h"

const std::string ITestScriptCase::TEST_SCRIPT_PASS_OUTPUT = "PASS";
const std::string ITestScriptCase::TEST_SCRIPT_FAIL_OUTPUT = "FAIL";

ITestScriptCase::ITestScriptCase(SSDInterface* ssdinterface, int number)
    : ssd(ssdinterface), number(number) {}

bool ITestScriptCase::ReadCompare(std::string lba, std::string expected) {
  unsigned int nLba = std::stoi(lba);
  std::string read = ssd->Read(nLba);
  if (expected == read) {
    return true;
  } else {
    std::cout << "ReadCompare FAIL: LBA " << lba << " expected: " << expected
              << " / read: " << read << std::endl;
    return false;
  }
}

std::string ITestScriptCase::GetRandomInputData() {
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<int> distrib(0, UINT_MAX);

  std::stringstream ss;
  ss << "0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(8)
     << distrib(gen);
  return ss.str();
}

void ITestScriptCase::PrintPassResult() {
  std::cout << TEST_SCRIPT_PASS_OUTPUT << std::endl;
}

void ITestScriptCase::PrintFailResult() {
  std::cout << TEST_SCRIPT_FAIL_OUTPUT << std::endl;
}
