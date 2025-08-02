#include "RealSSD.h"
#include "ILogger.h"
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
  RunExternalSSD(cmd);
  
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
  if (IsInvalidLBA(lba)) {
    return;
  }

  std::ostringstream cmd;
  cmd << ssdExe << " E " << lba << " " << size;
  execCommand(cmd.str());

  std::ifstream in(outputFile);
  std::string result;
  if (!in.good() || !std::getline(in, result)) {
    return;
  }
}

void RealSSD::Flush() {
  std::ostringstream cmd;
  cmd << ssdExe << " F";
  execCommand(cmd.str());
}

int RealSSD::execCommand(const std::string& cmd) {
  return std::system(cmd.c_str());
}

void RealSSD::RunExternalSSD(std::ostringstream& cmd) {
  ILogger::GetInstance()->LogPrint("RealSSD::RunExternalSSD", cmd.str(), false);
    execCommand(cmd.str());
}
