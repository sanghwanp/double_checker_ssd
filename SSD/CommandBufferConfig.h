#pragma once
#include "SSDConfig.h"
#include <string>

namespace CommandBufferConfig {
    static constexpr int MAX_LBA_CNT = ::MAX_LBA_CNT;
    static constexpr int INF = 0x3f3f3f3f;
    static constexpr int NOT_AVAILABLE = INF+1;
    static constexpr int MAX_BUFFER = 5;
    enum class CmdType { eREAD, WRITE, ERASE, INVALID };
};

