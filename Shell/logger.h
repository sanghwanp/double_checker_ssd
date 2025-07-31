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

  void print(const std::string& functionName, const std::string& message) override;
  void setConsoleOutput(bool on);

 private:
  std::string logFileName;
  std::ofstream logFile;
  ILogFileSystem* fileSystem;
  bool ownsFileSystem = false;
  bool consoleOutput;

  void openLogFile();
  std::string getCurrentTimestamp(bool forFile = false);
  void checkAndRotateLogFile();
  void manageOldLogs();
  bool ends_with(const std::string& str, const std::string& suffix);
};
