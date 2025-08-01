#pragma once
#include <string>
#include <string_view>

#include "GlobalConfig.h"
#include "SSDConfig.h"

namespace CommandBufferConfig {

constexpr int MAX_LBA_CNT = ::MAX_LBA_CNT;
constexpr int INF = 0x3f3f3f3f;
constexpr int NOT_AVAILABLE = INF + 1;
constexpr int MAX_BUF = 5;

inline constexpr std::string_view CMD_BUF_DIRPATH = "./buffer/";
inline constexpr std::string_view CMD_BUF_EXT = ".cmdbuf";

enum class CmdType { eREAD, WRITE, ERASE, INVALID };

inline std::string GetCmdTypeString(CmdType cmdType) {
  if (cmdType == CmdType::WRITE)
    return "WRITE";
  else if (cmdType == CmdType::ERASE)
    return "ERASE";
  else
    return "NOTHING";
}

};  // namespace CommandBufferConfig
