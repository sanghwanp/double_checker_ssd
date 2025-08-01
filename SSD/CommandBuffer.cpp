#include "CommandBuffer.h"

#include <map>
#include <string>
#include <string_view>
#include <iostream>

std::vector<CommandBufferEntry> CommandBuffer::LoadCmdsFromBuffer() const {
  static std::map<int, CommandBufferEntry> result_map;
  result_map.clear();

  std::filesystem::path curDirPath(GetAndMakeCmdBufferDirPath());
  std::vector<std::filesystem::path> cmdBufFiles = GetCmdbufFiles(curDirPath);
  for (const std::filesystem::path & cmdBufFile : cmdBufFiles) {
    std::string filename = cmdBufFile.filename().string();
    if (!MatchCmdBufFilename(filename)) continue;
    int order = GetOrderFromCmdBufFilename(filename);
    result_map[order] = MakeCmdBufEntry(filename);
  }

  std::vector<CommandBufferEntry> result;
  for (const auto& it : result_map) {
    result.emplace_back(it.second);
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
               CommandBufferConfig::COMMAND_BUFFER_FILEEXTENSION.data();
    filepath = std::string(GetAndMakeCmdBufferDirPath()) + filename;
    ofs.open(filepath);
    ofs.close();
  }
}

void CommandBuffer::FlushBuffer() {
  std::string_view cmdBufDirPath = GetAndMakeCmdBufferDirPath();
  auto cmdBufFiles = GetCmdbufFiles(std::filesystem::path(cmdBufDirPath));
  for (auto cmdBufFile : cmdBufFiles) {
    std::string filename = cmdBufFile.filename().u8string();
    if (!MatchCmdBufFilename(filename)) continue;
    std::filesystem::remove(cmdBufFile);
  }
}

std::vector<std::filesystem::path> CommandBuffer::GetCmdbufFiles(
    const std::filesystem::path& dirPath) const {
  std::vector<std::filesystem::path> cmdbufFiles;

  if (!std::filesystem::exists(dirPath) ||
      !std::filesystem::is_directory(dirPath)) {
    throw std::invalid_argument(std::string("Invalid directory: ") +
                                dirPath.u8string());
  }

  for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
    // std::cout << "plzrun: " << std::filesystem::absolute(entry.path()) <<
    // '\n'; std::cout << entry.path().extension().string() << "\n";
    if (entry.path().extension().string() ==
        CommandBufferConfig::COMMAND_BUFFER_FILEEXTENSION) {
      cmdbufFiles.push_back(entry.path());
    }
  }

  return cmdbufFiles;
}

bool CommandBuffer::MatchCmdBufFilename(const std::string& filename) const {
  return std::regex_match(filename, cmdBufFileRegexPattern);
}

unsigned int CommandBuffer::GetOrderFromCmdBufFilename(
    const std::string& filename) const {
  std::smatch match;
  std::regex_match(filename, match, cmdBufFileRegexPattern);

  unsigned int order = static_cast<unsigned int>(std::stoul(match[1].str()));
  return order;
}

CommandBufferEntry CommandBuffer::MakeCmdBufEntry(
    const std::string& filename) const {
  std::smatch match;
  std::regex_match(filename, match, cmdBufFileRegexPattern);

  std::string cmdTypeStr = match[2].str();
  CMD_TYPE cmdType;

  if (cmdTypeStr == "W")
    cmdType = eWriteCmd;
  else if (cmdTypeStr == "E")
    cmdType = eEraseCmd;
  else
    throw std::runtime_error("Invalid CMD_TYPE: " + cmdTypeStr);

  unsigned int startLba = static_cast<unsigned int>(std::stoul(match[3].str()));
  unsigned int endLba = static_cast<unsigned int>(std::stoul(match[4].str()));
  unsigned int data = static_cast<unsigned int>(std::stoul(match[5].str()));

  return CommandBufferEntry(cmdType, startLba, endLba, data);
}
