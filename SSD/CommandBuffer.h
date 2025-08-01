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
  void FlushBuffer();

 private:
  std::ifstream ifs;
  std::ofstream ofs;

  std::vector<std::filesystem::path> GetCmdbufFiles(
      const std::filesystem::path &dirPath) const;

  bool MatchCmdBufFilename(const std::string &filename) const;

  CommandBufferEntry MakeCmdBufEntry(const std::string &filename) const;
  unsigned int GetOrderFromCmdBufFilename(const std::string &filename) const;

  const std::regex cmdBufFileRegexPattern{
      R"(^(\d+)_(W|E)_(\d+)_(\d+)_(\d+)\.cmdbuf$)"};
};
