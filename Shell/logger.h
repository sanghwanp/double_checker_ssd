#pragma once

#include <string>
#include "ILogger.h"
#include "ILogFileSystem.h"

class Logger : public ILogger{
 public:
  static Logger& getInstance();  // Singleton 접근자

  void setConsoleOutput(bool on);
  void print(const std::string& location, const std::string& message);

 private:
  Logger();   // 생성자 private
  ~Logger();  // 소멸자

  Logger(const Logger&) = delete;             // 복사 금지
  Logger& operator=(const Logger&) = delete;  // 대입 금지

  bool consoleOutput;
  std::string logFileName;

  void openLogFile();
  std::string getCurrentTimestamp(bool forFile = false);
  void checkAndRotateLogFile();
  void manageOldLogs();
  bool ends_with(const std::string& str, const std::string& suffix);
};
