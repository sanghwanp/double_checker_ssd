// RealFileSystem.h
#include "LogFileSystem.h"
std::vector<fs::directory_entry> LogFileSystem::listFiles(
    const std::string& path) const {
  return std::vector<fs::directory_entry>(fs::directory_iterator(path), {});
}

bool LogFileSystem::isRegularFile(
    const fs::directory_entry& entry) const {
  return entry.is_regular_file();
}

std::string LogFileSystem::filename(
    const fs::directory_entry& entry) const {
  return entry.path().filename().string();
}

fs::file_time_type LogFileSystem::lastWriteTime(
    const fs::directory_entry& entry) const {
  return fs::last_write_time(entry);
}

void LogFileSystem::rename(const fs::path& from, const fs::path& to) {
  fs::rename(from, to);
}
