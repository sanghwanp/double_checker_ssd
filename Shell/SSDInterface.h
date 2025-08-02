#pragma once
#include <string>
using std::string;

class SSDInterface {
 public:
  virtual void Write(int lba, const string& value) = 0;
  virtual string Read(int lba) = 0;
  virtual void Erase(int lba, int size) = 0;
  virtual void Flush() = 0;

  inline bool IsInvalidLBA(int lba) { return lba < 0 || lba >= 100; };

  inline bool IsInvalidValue(const string& value) {
    if (value.size() != 10) return true;
    if (value[0] != '0' || value[1] != 'x') return true;

    for (int i = 2; i < 10; ++i) {
      char c = value[i];

      bool isDigit = ('0' <= c && c <= '9');
      bool isUpper = ('A' <= c && c <= 'F');
      bool isLower = ('a' <= c && c <= 'f');
      if (!(isDigit || isUpper || isLower)) return true;
    }

    return false;
  }

  inline bool IsInvalidErase(int lba, int size) {
    if (size < 0 || size > 10) {
      return true;
    }

    if (size == 0) {
      return false;
    }

    // assume lba is valid
    int lbaEnd = lba + size - 1;
    return lbaEnd >= 100;
  }
  inline string GetName() { return InterfaceName; }

 protected:
  string InterfaceName;
};
