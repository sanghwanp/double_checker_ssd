#include "SSDInterface.h"

class MockSSD : public SSDInterface {
 public:
  void Write(int lba, const string& value) override;
  string Read(int lba) override;

 private:
  int last_written_lba_ = -1;
  string last_written_value_;
};