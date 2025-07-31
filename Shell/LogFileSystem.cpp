#include <filesystem>

#include "LogFileSystem.h"

namespace fs = std::filesystem;

bool LogFileSystem::Exists(const fs::path& path) const {
  return fs::exists(path);
}
std::uintmax_t LogFileSystem::File_size(const fs::path& path) const {
  return fs::file_size(path);
}
std::vector<fs::directory_entry> LogFileSystem::ListFiles(
    const fs::path& dir) const {
  std::vector<fs::directory_entry> files;
  for (const auto& entry : fs::directory_iterator(dir)) {
    files.push_back(entry);
  }
  return files;
}
bool LogFileSystem::IsRegularFile(const fs::directory_entry& entry) const {
  return entry.is_regular_file();
}
std::string LogFileSystem::FileName(const fs::directory_entry& entry) const {
  return entry.path().filename().string();
}
fs::file_time_type LogFileSystem::LastWriteTime(
    const fs::directory_entry& entry) const {
  return fs::last_write_time(entry);
}
void LogFileSystem::Rename(const fs::path& from, const fs::path& to) {
  fs::rename(from, to);
}
