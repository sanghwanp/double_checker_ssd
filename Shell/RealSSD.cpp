#include "RealSSD.h"

#include <cstdlib>
#include <fstream>
#include <sstream>

RealSSD::RealSSD(const std::string& ssdExecutable,
                 const std::string& outputFile)
    : ssdExe(ssdExecutable), outputFile(outputFile) {}

void RealSSD::Write(int lba, const std::string& value) {
  if (IsInvalidLBA(lba) || IsInvalidValue(value)) {
    return;
  }

  std::ostringstream cmd;
  cmd << ssdExe << " W " << lba << " " << value;
  execCommand(cmd.str());

  std::ifstream in(outputFile);
  std::string result;
  if (!in.good() || !std::getline(in, result)) {
    return;
  }
}

std::string RealSSD::Read(int lba) {
  if (IsInvalidLBA(lba)) {
    return "ERROR";
  }

  std::ostringstream cmd;
  cmd << ssdExe << " R " << lba;
  int ret = execCommand(cmd.str());

  std::ifstream in(outputFile);
  std::string line;

  if (!in.good() || !std::getline(in, line)) {
    return "ERROR";
  }
  return line;
}

void RealSSD::Erase(int lba, int size) {
  throw std::runtime_error("RealSSD::Erase() Not implemented");
}

void RealSSD::Flush() {
  std::ostringstream cmd;
  cmd << ssdExe << " F";
  execCommand(cmd.str());
}

int RealSSD::execCommand(const std::string& cmd) {
  return std::system(cmd.c_str());
}

bool RealSSD::IsInvalidLBA(int lba) { return lba < 0 || lba >= 100; }

bool RealSSD::IsInvalidValue(const string& value) {
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
