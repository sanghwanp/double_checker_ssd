#include "SSDInterface.h"

class MockSSD : public SSDInterface {
  void SSDWrite(int lba, const string& value) override;
  string SSDRead(int lba) override;
};