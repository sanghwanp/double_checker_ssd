#pragma once
#include <unordered_map>

#include "SSDInterface.h"

class MockSSD : public SSDInterface {
 public:
  void Write(int lba, const string& value) override;
  string Read(int lba) override;
  void Erase(int lba, int size) override;
  bool IsInvalidLBA(int lba);
  bool IsInvalidValue(const string& value);

 private:
  std::unordered_map<int, string> cache;
};