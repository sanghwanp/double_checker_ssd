#pragma once
#include <string>
#include <string_view>

#include "SSDConfig.h"

namespace CommandBufferConfig {
constexpr int MAX_LBA_CNT = ::MAX_LBA_CNT;
constexpr int INF = 0x3f3f3f3f;
constexpr int NOT_AVAILABLE = INF + 1;
constexpr int MAX_BUFFER = 5;
inline constexpr std::string_view COMMAND_BUFFER_DIRPATH = "./buffer/";
inline constexpr std::string_view COMMAND_BUFFER_FILEEXTENSION = ".cmdbuf";

enum class CmdType { eREAD, WRITE, ERASE, INVALID };
};  // namespace CommandBufferConfig
