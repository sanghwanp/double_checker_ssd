#include "CommandBuffer.h"

#include <filesystem>
#include <iostream>
#include <map>
#include <string>
#include <string_view>

using Path = std::filesystem::path;

std::vector<CommandBufferEntry> CommandBuffer::LoadCmdsFromFile() const {
  static std::map<int, CommandBufferEntry> result_map;
  result_map.clear();

  Path bufferDirPath(EnsureCommandBufferDirExistAndGetPath());
  std::vector<Path> commandBufferFilePaths = GetCommandBufferFilePaths(bufferDirPath);
  for (const Path& commandBufferFilePath : commandBufferFilePaths) {
    std::string filename = commandBufferFilePath.filename().string();
    if (not(MatchCommandBufferFilename(filename))) continue;
    int order = GetOrderFromCmdBufFilename(filename);
    result_map[order] = MakeCommandBufferEntry(filename);
  }

  static std::vector<CommandBufferEntry> result;
  result.clear();

  for (const auto& it : result_map) {
    const CommandBufferEntry& commandBufferEntry = it.second;
    result.emplace_back(commandBufferEntry);
  }
  return result;
}

void CommandBuffer::WriteCmdsToBuffer(
    const std::vector<CommandBufferEntry>& cmds) {
  FlushBuffer();
  std::string filename, filepath, order;
  for (int i = 0; i < cmds.size(); i++) {
    const CommandBufferEntry& cmd = cmds[i];
    order = std::to_string(i);
    filename = order + "_" + cmd.ToString() +
               CommandBufferConfig::CMD_BUF_EXT.data();
    filepath = std::string(EnsureCommandBufferDirExistAndGetPath()) + filename;
    ofs.open(filepath);
    ofs.close();
  }
}

void CommandBuffer::FlushBuffer() {
  std::string_view cmdBufDirPath = EnsureCommandBufferDirExistAndGetPath();
  auto cmdBufFiles = GetCommandBufferFilePaths(Path(cmdBufDirPath));
  for (auto cmdBufFile : cmdBufFiles) {
    std::string filename = cmdBufFile.filename().u8string();
    if (not(MatchCommandBufferFilename(filename))) continue;
    std::filesystem::remove(cmdBufFile);
  }
}

std::vector<Path> CommandBuffer::GetCommandBufferFilePaths(const Path& dirPath) const {
  std::vector<Path> cmdbufFiles;

  if (not(std::filesystem::exists(dirPath)) ||
      not(std::filesystem::is_directory(dirPath))) {
    throw std::invalid_argument(std::string("Invalid directory: ") +
                                dirPath.u8string());
  }

  for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
    // std::cout << "plzrun: " << std::filesystem::absolute(entry.path()) <<
    // '\n'; std::cout << entry.path().extension().string() << "\n";
    if (entry.path().extension().string() ==
        CommandBufferConfig::CMD_BUF_EXT) {
      cmdbufFiles.push_back(entry.path());
    }
  }

  return cmdbufFiles;
}

bool CommandBuffer::MatchCommandBufferFilename(
    const std::string& filename) const {
  return std::regex_match(filename, cmdBufFileRegexPattern);
}

unsigned int CommandBuffer::GetOrderFromCmdBufFilename(
    const std::string& filename) const {
  std::smatch match;
  std::regex_match(filename, match, cmdBufFileRegexPattern);

  unsigned int order = static_cast<unsigned int>(std::stoul(match[1].str()));
  return order;
}

CommandBufferEntry CommandBuffer::MakeCommandBufferEntry(
    const std::string& filename) const {
  std::smatch match;
  std::regex_match(filename, match, cmdBufFileRegexPattern);

  std::string cmdTypeStr = match[2].str();
  CommandBufferConfig::CmdType cmdType;

  if (cmdTypeStr == "W")
    cmdType = CommandBufferConfig::CmdType::WRITE;
  else if (cmdTypeStr == "E")
    cmdType = CommandBufferConfig::CmdType::ERASE;
  else
    throw std::runtime_error("Invalid CmdType: " + cmdTypeStr);

  unsigned int startLba = static_cast<unsigned int>(std::stoul(match[3].str()));
  unsigned int endLba = static_cast<unsigned int>(std::stoul(match[4].str()));
  unsigned int data = static_cast<unsigned int>(std::stoul(match[5].str()));

  return CommandBufferEntry(cmdType, startLba, endLba, data);
}
