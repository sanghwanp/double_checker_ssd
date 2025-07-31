#pragma once

#include <fstream>
#include <memory>
#include <string>

#include "ILogFileSystem.h"
#include "ILogger.h"

class Logger : public ILogger {
 public:
  Logger();
  Logger(ILogFileSystem* fs, bool ConsoleOn);
  ~Logger();

  void Print(const std::string& functionName, const std::string& message) override;
  void SetConsoleOutput(bool on);

 private:
  std::string logFileName;
  std::ofstream logFile;
  ILogFileSystem* fileSystem;
  bool ownsFileSystem = false;
  bool consoleOutput;

  void OpenLogFile();
  std::string GetCurrentTimestamp(bool forFile = false);
  void CheckAndRotateLogFile();
  void ManageOldLogs();
  bool Ends_with(const std::string& str, const std::string& suffix);
};
