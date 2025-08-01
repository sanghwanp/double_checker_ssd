#pragma once
#include "SSDConfig.h"
#include <string>

struct CommandBufferConfig {
    static constexpr int MAX_LBA_CNT = ::MAX_LBA_CNT;
    static constexpr int INF = 0x3f3f3f3f;
    static constexpr int NotAvailable = INF+1;
};

