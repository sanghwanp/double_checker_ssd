#include <unordered_map>

#include "SSDInterface.h"

class MockSSD : public SSDInterface {
 public:
  void Write(int lba, const string& value) override;
  string Read(int lba) override;

 private:
  std::unordered_map<int, std::string> storage;
};