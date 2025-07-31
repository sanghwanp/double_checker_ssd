#include "Logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "LogFileSystem.h"

namespace {
constexpr std::uintmax_t MAX_FILE_SIZE = 10 * 1024;  // 10KB
}

Logger::Logger()
    : consoleOutput(true),
      logFileName("latest.log"),
      fileSystem(new LogFileSystem()),
      ownsFileSystem(true) {
  openLogFile();
}

Logger::Logger(ILogFileSystem* fs, bool ConsoleOn)
    : consoleOutput(ConsoleOn),
      logFileName("latest.log"),
      fileSystem(fs),
      ownsFileSystem(false) {
  openLogFile();
}

Logger::~Logger() {
  if (logFile.is_open()) {
    logFile.close();
  }
  if (ownsFileSystem) {
    delete fileSystem;
  }
}

void Logger::setConsoleOutput(bool on) { consoleOutput = on; }

void Logger::print(const std::string& functionName,
                   const std::string& message) {
  std::string timestamp = getCurrentTimestamp();
  std::ostringstream formatted;

  std::ostringstream funcOss;
  funcOss << std::left << std::setw(40) << functionName;

  formatted << "[" << timestamp << "] " << funcOss.str() << ": " << message;
  std::string logLine = formatted.str();

  if (consoleOutput) {
    std::cout << logLine << std::endl;
  }

  if (logFile.is_open()) {
    logFile << logLine << std::endl;
    logFile.flush();
    checkAndRotateLogFile();
  }
}

void Logger::openLogFile() { logFile.open(logFileName, std::ios::app); }

std::string Logger::getCurrentTimestamp(bool forFile) {
  using namespace std::chrono;
  auto now = system_clock::now();
  std::time_t t = system_clock::to_time_t(now);
  std::tm localTime{};
#if defined(_WIN32) || defined(_WIN64)
  localtime_s(&localTime, &t);
#else
  localtime_r(&t, &localTime);
#endif

  std::ostringstream oss;
  if (forFile) {
    oss << std::setfill('0') << std::setw(2) << (localTime.tm_year % 100)
        << std::setw(2) << (localTime.tm_mon + 1) << std::setw(2)
        << localTime.tm_mday << "_" << std::setw(2) << localTime.tm_hour
        << std::setw(2) << localTime.tm_min;
  } else {
    oss << std::setfill('0') << std::setw(2) << (localTime.tm_year % 100) << "."
        << std::setw(2) << (localTime.tm_mon + 1) << "." << std::setw(2)
        << localTime.tm_mday << " " << std::setw(2) << localTime.tm_hour << ":"
        << std::setw(2) << localTime.tm_min;
  }

  return oss.str();
}

void Logger::checkAndRotateLogFile() {
  if (!fileSystem->exists(logFileName)) return;

  std::uintmax_t fileSize = fileSystem->file_size(logFileName);
  if (fileSize < MAX_FILE_SIZE) return;

  logFile.close();

  std::string rotatedName = "until_" + getCurrentTimestamp(true) + ".log";
  fileSystem->rename(logFileName, rotatedName);

  openLogFile();
  manageOldLogs();
}

bool Logger::ends_with(const std::string& str, const std::string& suffix) {
  if (str.length() < suffix.length()) return false;
  return str.compare(str.length() - suffix.length(), suffix.length(), suffix) ==
         0;
}

void Logger::manageOldLogs() {
  std::vector<std::filesystem::directory_entry> untilLogs;

  for (const auto& entry : fileSystem->listFiles(".")) {
    if (fileSystem->isRegularFile(entry)) {
      std::string name = fileSystem->filename(entry);
      if (name.rfind("until_", 0) == 0 && ends_with(name, ".log")) {
        untilLogs.push_back(entry);
      }
    }
  }

  if (untilLogs.size() <= 1) return;

  std::sort(
      untilLogs.begin(), untilLogs.end(), [&](const auto& a, const auto& b) {
        return fileSystem->lastWriteTime(a) < fileSystem->lastWriteTime(b);
      });
  untilLogs.pop_back();  // Remove the most recent log
  for (auto oldLog : untilLogs) {
    std::filesystem::path zipPath = oldLog.path();
    zipPath.replace_extension(".zip");
    fileSystem->rename(oldLog.path(), zipPath);
  } 
}
