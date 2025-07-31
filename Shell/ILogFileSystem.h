#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class ILogFileSystem {
 public:
  virtual ~ILogFileSystem() = default;

  virtual bool exists(const fs::path& path) const = 0;
  virtual std::uintmax_t file_size(const fs::path& path) const = 0;
  virtual std::vector<fs::directory_entry> listFiles(
      const fs::path& dir) const = 0;
  virtual bool isRegularFile(const fs::directory_entry& entry) const = 0;
  virtual std::string filename(const fs::directory_entry& entry) const = 0;
  virtual fs::file_time_type lastWriteTime(
      const fs::directory_entry& entry) const = 0;
  virtual void rename(const fs::path& from, const fs::path& to) = 0;
};
