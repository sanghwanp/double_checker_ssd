#pragma once
#include <filesystem>
#include <fstream>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

#include "CommandBufferEntry.h"
class CommandBuffer {
 public:
  std::vector<CommandBufferEntry> LoadCmdsFromFile() const;
  void WriteCmdsToBuffer(const std::vector<CommandBufferEntry> &cmds);
  void FlushBuffer();

 private:
  std::ifstream ifs;
  std::ofstream ofs;

  std::vector<std::filesystem::path> GetCommandBufferFilePaths(
      const std::filesystem::path &dirPath) const;

  bool MatchCommandBufferFilename(const std::string &filename) const;

  CommandBufferEntry MakeCommandBufferEntry(const std::string &filename) const;
  unsigned int GetOrderFromCmdBufFilename(const std::string &filename) const;

  std::string_view EnsureCommandBufferDirExistAndGetPath() const {
    std::string_view cmdBufDirPath =
        CommandBufferConfig::CMD_BUF_DIRPATH;
    if (not(std::filesystem::exists(cmdBufDirPath))) {
      std::filesystem::create_directories(cmdBufDirPath);
    }
    return cmdBufDirPath;
  }

  const std::regex cmdBufFileRegexPattern{
      R"(^(\d+)_(W|E)_(\d+)_(\d+)_(\d+)\.cmdbuf$)"};
};
