#pragma once
#include <string>
#include <string_view>

#include "SSDConfig.h"
#include "Types.h"

namespace CommandBufferConfig {
constexpr int MIN_LBA = ::MIN_LBA;
constexpr int MAX_LBA = ::MAX_LBA;
constexpr int MAX_LBA_CNT = ::MAX_LBA_CNT;
constexpr int LBA_ERASE_RANGE_LIMIT = 10;
constexpr int INF = 0x3f3f3f3f;
constexpr int NOT_AVAILABLE = INF + 1;
constexpr int MAX_BUFFER = 5;
inline constexpr std::string_view COMMAND_BUFFER_DIRPATH = "./buffer/";
inline constexpr std::string_view COMMAND_BUFFER_FILEEXTENSION = ".cmdbuf";

inline std::string GetCmdTypeString(CMD_TYPE cmdType) {
  if (cmdType == eWriteCmd)
    return "WRITE";
  else if (cmdType == eEraseCmd)
    return "ERASE";
  else
    return "NOTHING";
}
};  // namespace CommandBufferConfig
