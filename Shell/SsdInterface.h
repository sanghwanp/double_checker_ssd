#include<string>
using std::string;

class SSDInterface {
 public:
  virtual void SsdWrite(int lba, const std::string& value) = 0;
  virtual string SsdRead(int lba) = 0;
};