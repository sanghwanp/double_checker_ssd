#pragma once
#include <unordered_map>

#include "SSDInterface.h"

class MockSSD : public SSDInterface {
 public:
  MockSSD() { InterfaceName = "Fake SSD Driver"; } 
  void Write(int lba, const string& value) override;
  string Read(int lba) override;
  void Erase(int lba, int size) override;
  void Flush() override;

 private:
  std::unordered_map<int, string> cache;
};
