#pragma once
#include "ILogFileSystem.h"
class LogFileSystem : public ILogFileSystem {
 public:
  std::vector<fs::directory_entry> listFiles(
      const std::string& path) const override;
  bool isRegularFile(const fs::directory_entry& entry) const;
  std::string filename(const fs::directory_entry& entry) const;
  fs::file_time_type lastWriteTime(const fs::directory_entry& entry) const;
  void rename(const fs::path& from, const fs::path& to);

  private:
  ILogFileSystem* fileSystem;
};
