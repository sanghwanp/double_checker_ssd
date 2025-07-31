#pragma once
#include <unordered_map>

#include "gmock/gmock.h"
#include "SSDInterface.h"

class MockSSD : public SSDInterface {
 public:
  void Write(int lba, const string& value) override;
  string Read(int lba) override;
  void Erase(int lba, int size) override;
  MOCK_METHOD(void, Flush, (), (override));

  bool IsInvalidLBA(int lba);
  bool IsInvalidValue(const string& value);
  bool IsInvalidErase(int lba, int size);

 private:
  std::unordered_map<int, string> cache;
};