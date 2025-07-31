#pragma once
#include <string>

#include "SSDInterface.h"

class RealSSD : public SSDInterface {
 public:
  RealSSD(const std::string& ssdExecutable = "ssd.exe",
          const std::string& outputFile = "ssd_output.txt");
  void Write(int lba, const string& value) override;
  string Read(int lba) override;
  void Erase(int lba, int size) override;
  void Flush() override;

  bool IsInvalidLBA(int lba);
  bool IsInvalidValue(const string& value);
  virtual int execCommand(const std::string& cmd);

 private:
  std::string ssdExe;
  std::string outputFile;
};