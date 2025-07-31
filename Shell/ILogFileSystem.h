#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class ILogFileSystem {
 public:
  virtual ~ILogFileSystem() = default;

  virtual bool Exists(const fs::path& path) const = 0;
  virtual std::uintmax_t File_size(const fs::path& path) const = 0;
  virtual std::vector<fs::directory_entry> ListFiles(
      const fs::path& dir) const = 0;
  virtual bool IsRegularFile(const fs::directory_entry& entry) const = 0;
  virtual std::string FileName(const fs::directory_entry& entry) const = 0;
  virtual fs::file_time_type LastWriteTime(
      const fs::directory_entry& entry) const = 0;
  virtual void Rename(const fs::path& from, const fs::path& to) = 0;
};
