
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "Logger.h"
#include "LogFileSystem.h"

namespace {
constexpr std::uintmax_t MAX_FILE_SIZE = 10 * 1024;  // 10KB
}

ILogger* ILogger::GetInstance() { return &Logger::GetInstance(); }
Logger::Logger()
    : consoleOutput(true),
      logFileName("latest.log"),
      ownFilesystem(new LogFileSystem()),
      internalFsFlag(true) {
  fileSystem = ownFilesystem;
  OpenLogFile();
}



Logger::~Logger() {
  if (logFile.is_open()) {
    logFile.close();
  }
}

void Logger::SetLoggerFileSystem(ILogFileSystem* fs) {
  fileSystem = fs;
  internalFsFlag = false;
}
void Logger::RestoreLoggerFileSystem(void) {
  fileSystem = ownFilesystem;
  internalFsFlag = true;
  if (fileSystem == nullptr)
  {
    std::cout << "fileSystem is nullptr !!\n";
  }
}

void Logger::SetConsoleOutput(bool on) { consoleOutput = on; }

void Logger::LogPrint(const std::string& functionName,
                      const std::string& message, bool bConsole) {
  std::string timestamp = GetCurrentTimestamp();
  std::ostringstream formatted;
  std::ostringstream funcOss;

  // 항상 파일 정리를 먼저해서 현재 log는 항상 latest.log 파일에 기록 될 수 있도록 한다.
  CheckAndRotateLogFile();

  funcOss << std::left << std::setw(30) << functionName;

  formatted << "[" << timestamp << "] " << funcOss.str() << ": " << message;
  std::string logLine = formatted.str();

  if ((consoleOutput == true && bConsole == true)) {
    std::cout << logLine << std::endl;
  }

  logFile << logLine << std::endl;
  logFile.flush();
}

void Logger::OpenLogFile() { logFile.open(logFileName, std::ios::app); }

std::string Logger::GetCurrentTimestamp(bool forFile) {
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
        << localTime.tm_mday << "_" << std::setw(2) << localTime.tm_hour << "h_"
        << std::setw(2) << localTime.tm_min << "m_" << std::setw(2)
        << localTime.tm_sec << "s";
  } else {
    oss << std::setfill('0') << std::setw(2) << (localTime.tm_year % 100) << "."
        << std::setw(2) << (localTime.tm_mon + 1) << "." << std::setw(2)
        << localTime.tm_mday << " " << std::setw(2) << localTime.tm_hour << ":"
        << std::setw(2) << localTime.tm_min << ":" << std::setw(2)
        << localTime.tm_sec;
  }

  return oss.str();
}

void Logger::CheckAndRotateLogFile() {
  if (!fileSystem->Exists(logFileName)) return;

  std::uintmax_t fileSize = fileSystem->File_size(logFileName);
  if (fileSize < MAX_FILE_SIZE) return;

  logFile.flush();
  logFile.close();

  std::string rotatedName = GenerateUniqueLogFileName("until_" + GetCurrentTimestamp(true));

  fileSystem->Rename(logFileName, rotatedName);

  OpenLogFile();
  ManageOldLogs();
}
std::string Logger::GenerateUniqueLogFileName(const std::string& baseName) {
  std::string extension = ".log";
  std::string fileName = baseName + extension;

  if (!std::filesystem::exists(fileName)) {
    return fileName;
  }

  for (int counter = 0;; ++counter) {
    std::ostringstream oss;
    oss << baseName << "_" << counter << extension;
    std::string newName = oss.str();
    if (!std::filesystem::exists(newName)) {
      return newName;
    }
  }
}
bool Logger::Ends_with(const std::string& str, const std::string& suffix) {
  if (str.length() < suffix.length()) return false;
  return str.compare(str.length() - suffix.length(), suffix.length(), suffix) ==
         0;
}

void Logger::ManageOldLogs() {
  std::vector<std::filesystem::directory_entry> untilLogs;

  for (const auto& entry : fileSystem->ListFiles(".")) {
    if (fileSystem->IsRegularFile(entry)) {
      std::string name = fileSystem->FileName(entry);
      if (name.rfind("until_", 0) == 0 && Ends_with(name, ".log")) {
        untilLogs.push_back(entry);
      }
    }
  }

  if (untilLogs.size() <= 1) return;

  std::sort(
      untilLogs.begin(), untilLogs.end(), [&](const auto& a, const auto& b) {
        return fileSystem->LastWriteTime(a) < fileSystem->LastWriteTime(b);
      });
  untilLogs.pop_back();  // Remove the most recent log
  for (auto oldLog : untilLogs) {
    std::filesystem::path zipPath = oldLog.path();
    zipPath.replace_extension(".zip");
    fileSystem->Rename(oldLog.path(), zipPath);
  } 
}
