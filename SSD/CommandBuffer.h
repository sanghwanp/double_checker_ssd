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
  std::vector<CommandBufferEntry> LoadCmdsFromBuffer() const;
  void WriteCmdsToBuffer(const std::vector<CommandBufferEntry> &cmds);
  void FlushBuffer(bool isEnabledMakeEmptyFile);

 private:
  std::ifstream ifs;
  std::ofstream ofs;

  std::vector<std::filesystem::path> GetCmdbufFiles(
      const std::filesystem::path &dirPath) const;

  bool MatchCmdBufNormalFilename(const std::string &filename) const;
  bool MatchCmdBufEmptyFilename(const std::string &filename) const;

  CommandBufferEntry MakeCmdBufEntry(const std::string &filename) const;
  unsigned int GetOrderFromCmdBufFilename(const std::string &filename) const;

  std::string_view GetAndMakeCmdBufferDirPath() const {
    std::string_view cmdBufDirPath =
        CommandBufferConfig::COMMAND_BUFFER_DIRPATH;
    if (!std::filesystem::exists(cmdBufDirPath)) {
      std::filesystem::create_directories(cmdBufDirPath);
    }
    return cmdBufDirPath;
  }

  const std::regex cmdBufFileNormalRegexPattern{
      R"(^(\d+)_(W|E)_(\d+)_(\d+)_(\d+)\.cmdbuf$)"};

  const std::regex cmdBufFileEmptyRegexPattern{R"(^(\d+)_Empty\.cmdbuf$)"};
};
