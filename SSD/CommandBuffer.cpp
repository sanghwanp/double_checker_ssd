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
    CommandBufferEntry& objCmdEntry = MakeCmdBufEntry(filename);

    // empty file handling
    if (objCmdEntry.cmdType == eInvalidCmd) continue;

    result_map[order] = objCmdEntry;
  }

  std::vector<CommandBufferEntry> result;
  for (const auto& it : result_map) {
    result.emplace_back(it.second);
  }
  return result;
}

void CommandBuffer::WriteCmdsToBufferFiles(
    const std::vector<CommandBufferEntry>& cmds) {
  DeleteAllFilesInBufferDir();

  // make 5 buffer files
  for (int i = 0; i < CommandBufferConfig::MAX_BUFFER; i++) {
      if (cmds.size() > i)
      {
          const CommandBufferEntry& cmd = cmds[i];
          SaveCmdBufferfile(i, cmd);
      }
      else
      {
          CommandBufferEntry emptyCmd(eInvalidCmd);
          // make empty files
          SaveCmdBufferfile(i, emptyCmd);
      }
  }
}

void CommandBuffer::SaveCmdBufferfile(int fileNumber, const CommandBufferEntry& cmd)
{
    std::string filepath;
    std::string filename;
    std::string order;
    order = std::to_string(fileNumber + 1);
    filename = order + "_" + cmd.ToString();
    filepath = std::string(GetAndMakeCmdBufferDirPath()) + filename;
    ofs.open(filepath);
    ofs.close();
}

void CommandBuffer::DeleteAllFilesInBufferDir() {
  std::string_view cmdBufDirPath = GetAndMakeCmdBufferDirPath();
  auto cmdBufFiles = GetCmdbufFiles(std::filesystem::path(cmdBufDirPath));
  for (auto cmdBufFile : cmdBufFiles) {
    // 모든 파일 그냥 다 지워
    //std::string filename = cmdBufFile.filename().u8string();
    //if (!MatchCmdBufFilename(filename)) continue;
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
      cmdbufFiles.push_back(entry.path());
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

  std::regex_match(filename, match, cmdRegexPattern);

  std::string cmdTypeStr = match[1].str();
  CMD_TYPE cmdType;

  if (cmdTypeStr == "W")
    cmdType = eWriteCmd;
  else if (cmdTypeStr == "E")
    cmdType = eEraseCmd;
  else
  {
      cmdType = eInvalidCmd;
      return CommandBufferEntry(cmdType, 0, 0, 0);
  }

  unsigned int startLba = static_cast<unsigned int>(std::stoul(match[2].str()));
  unsigned int endLba = static_cast<unsigned int>(std::stoul(match[3].str()));
  unsigned int data = 0;
  if (cmdType == eWriteCmd)  data = static_cast<unsigned int>(std::stoul(match[4].str()));

  return CommandBufferEntry(cmdType, startLba, endLba, data);
}
