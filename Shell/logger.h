#pragma once

#include <fstream>
#include <memory>
#include <string>

#include "ILogFileSystem.h"
#include "ILogger.h"

class Logger : public ILogger {
 public:
  ~Logger();

  void LogPrint(const std::string& functionName, const std::string& message,
                bool bConsole = true) override;
  void SetConsoleOutput(bool on) override;
  static Logger& GetInstance() {
    static Logger instance;
    return instance;
  }
  void SetLoggerFileSystem(ILogFileSystem* fs);
  void RestoreLoggerFileSystem(void);

 private:
  std::string logFileName;
  std::ofstream logFile;
  ILogFileSystem* fileSystem;
  ILogFileSystem* ownFilesystem;

  bool internalFsFlag = false;
  bool consoleOutput;

  Logger();

  void OpenLogFile();
  std::string GetCurrentTimestamp(bool forFile = false);
  void CheckAndRotateLogFile();
  std::string GenerateUniqueLogFileName(const std::string& baseName);
  void ManageOldLogs();
  bool Ends_with(const std::string& str, const std::string& suffix);
};


