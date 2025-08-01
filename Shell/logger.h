#pragma once

#include <fstream>
#include <memory>
#include <string>

#include "ILogFileSystem.h"
#include "ILogger.h"

class Logger : public ILogger {
 public:
  ~Logger();

  void LogPrint(const std::string& functionName, const std::string& message) override;
  void MyPrint(const std::string& message) override;
  void SetConsoleOutput(bool on);
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
  ILogFileSystem* ownsfileSystem;

  bool ownsFileSystem = false;
  bool consoleOutput;

  Logger();

  void OpenLogFile();
  std::string GetCurrentTimestamp(bool forFile = false);
  void CheckAndRotateLogFile();
  std::string GenerateUniqueLogFileName(const std::string& baseName);
  void ManageOldLogs();
  bool Ends_with(const std::string& str, const std::string& suffix);
};


