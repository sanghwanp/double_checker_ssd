#include "RealSSD.h"

#include <cstdlib>
#include <fstream>
#include <sstream>

RealSSD::RealSSD(const std::string& ssdExecutable,
                 const std::string& outputFile)
    : ssdExe(ssdExecutable), outputFile(outputFile) {}

void RealSSD::Write(int lba, const std::string& value) {
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

// �⺻ execCommand ����: std::system ���
int RealSSD::execCommand(const std::string& cmd) {
  return std::system(cmd.c_str());
}