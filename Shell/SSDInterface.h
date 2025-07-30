#include <string>
using std::string;

class SSDInterface {
 public:
  virtual void Write(int lba, const string& value) = 0;
  virtual string Read(int lba) = 0;
};
