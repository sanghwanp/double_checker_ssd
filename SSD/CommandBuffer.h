#pragma once
#include "CommandBufferEntry.h"
#include <vector>
class CommandBuffer
{
public:
    std::vector<CommandBufferEntry> LoadCmdsFromBuffer() const {
        return std::vector<CommandBufferEntry>();
    }
    void WriteCmdsToBuffer(const std::vector<CommandBufferEntry> & cmds) {}
    void FlushBuffer() {}
};

