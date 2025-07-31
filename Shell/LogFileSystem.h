#pragma once
#include "ILogFileSystem.h"

class LogFileSystem : public ILogFileSystem {
 public:
  bool Exists(const std::filesystem::path& path) const override;
  std::uintmax_t File_size(const std::filesystem::path& path) const override;
  std::vector<std::filesystem::directory_entry> ListFiles(
      const std::filesystem::path& dir) const override;
  bool IsRegularFile(
      const std::filesystem::directory_entry& entry) const override;
  std::string FileName(
      const std::filesystem::directory_entry& entry) const override;
  std::filesystem::file_time_type LastWriteTime(
      const std::filesystem::directory_entry& entry) const override;
  void Rename(const std::filesystem::path& from,
              const std::filesystem::path& to) override;
};
