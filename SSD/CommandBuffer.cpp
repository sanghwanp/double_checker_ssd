#include "CommandBuffer.h"

std::vector<CommandBufferEntry> CommandBuffer::LoadCmdsFromBuffer() const {
  std::vector<CommandBufferEntry> result;
  std::filesystem::path curDirPath("./");
  auto cmdBufFiles = GetCmdbufFiles(std::filesystem::path(curDirPath));
  for (auto cmdBufFile : cmdBufFiles) {
    std::string filename = cmdBufFile.u8string();
    if (!MatchCmdBufFilename(filename)) continue;
    result.push_back(MakeCmdBufEntry(filename));
  }

  return result;
}

void CommandBuffer::WriteCmdsToBuffer(
    const std::vector<CommandBufferEntry>& cmds) {
  FlushBuffer();
  std::string filename;
  for (const CommandBufferEntry& cmd : cmds) {
    filename = cmd.ToString() + ".cmdbuf";
    ofs.open(filename);
    ofs.close();
  }
}

void CommandBuffer::FlushBuffer() {
  std::filesystem::path curDirPath("./");
  auto cmdBufFiles = GetCmdbufFiles(std::filesystem::path(curDirPath));
  for (auto cmdBufFile : cmdBufFiles) {
    std::string filename = cmdBufFile.u8string();
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
    if (entry.is_regular_file() && entry.path().extension() == ".cmdbuf") {
      cmdbufFiles.push_back(entry.path());
    }
  }

  return cmdbufFiles;
}

bool CommandBuffer::MatchCmdBufFilename(const std::string& filename) const {
  return std::regex_match(filename, cmdBufFileRegexPattern);
}

CommandBufferEntry CommandBuffer::MakeCmdBufEntry(
    const std::string& filename) const {
  std::smatch match;
  std::regex_match(filename, match, cmdBufFileRegexPattern);

  std::string cmdTypeStr = match[1].str();
  CommandBufferConfig::CmdType cmdType;

  if (cmdTypeStr == "W")
    cmdType = CommandBufferConfig::CmdType::WRITE;
  else if (cmdTypeStr == "E")
    cmdType = CommandBufferConfig::CmdType::ERASE;
  else
    throw std::runtime_error("Invalid CmdType: " + cmdTypeStr);

  unsigned int startLba = static_cast<unsigned int>(std::stoul(match[2].str()));
  unsigned int endLba = static_cast<unsigned int>(std::stoul(match[3].str()));
  unsigned int data = static_cast<unsigned int>(std::stoul(match[4].str()));

  return CommandBufferEntry(cmdType, startLba, endLba, data);
}
