#pragma once
#include "ILogFileSystem.h"

class LogFileSystem : public ILogFileSystem {
 public:
  bool exists(const std::filesystem::path& path) const override;
  std::uintmax_t file_size(const std::filesystem::path& path) const override;
  std::vector<std::filesystem::directory_entry> listFiles(
      const std::filesystem::path& dir) const override;
  bool isRegularFile(
      const std::filesystem::directory_entry& entry) const override;
  std::string filename(
      const std::filesystem::directory_entry& entry) const override;
  std::filesystem::file_time_type lastWriteTime(
      const std::filesystem::directory_entry& entry) const override;
  void rename(const std::filesystem::path& from,
              const std::filesystem::path& to) override;
};
