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
  void WriteCmdsToBufferFiles(const std::vector<CommandBufferEntry> &cmds);

  void DeleteAllFilesInBufferDir();

 private:
  std::ifstream ifs;
  std::ofstream ofs;

  std::vector<std::filesystem::path> GetCmdbufFiles(
      const std::filesystem::path &dirPath) const;

  bool MatchCmdBufFilename(const std::string &filename) const;
  void SaveCmdBufferfile(int fileNumber, const CommandBufferEntry& cmd);
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

  const std::regex cmdBufFileRegexPattern{
      R"(([1-5])_(.*))"};
  const std::regex cmdRegexPattern{
  R"(^[1-5]_([EW])_(\d+)_(\d+)_?(\d+))" };
};
