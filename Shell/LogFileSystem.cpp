#include <filesystem>

#include "LogFileSystem.h"

namespace fs = std::filesystem;

bool LogFileSystem::exists(const fs::path& path) const {
  return fs::exists(path);
}
std::uintmax_t LogFileSystem::file_size(const fs::path& path) const {
  return fs::file_size(path);
}
std::vector<fs::directory_entry> LogFileSystem::listFiles(
    const fs::path& dir) const {
  std::vector<fs::directory_entry> files;
  for (const auto& entry : fs::directory_iterator(dir)) {
    files.push_back(entry);
  }
  return files;
}
bool LogFileSystem::isRegularFile(const fs::directory_entry& entry) const {
  return entry.is_regular_file();
}
std::string LogFileSystem::filename(const fs::directory_entry& entry) const {
  return entry.path().filename().string();
}
fs::file_time_type LogFileSystem::lastWriteTime(
    const fs::directory_entry& entry) const {
  return fs::last_write_time(entry);
}
void LogFileSystem::rename(const fs::path& from, const fs::path& to) {
  fs::rename(from, to);
}
