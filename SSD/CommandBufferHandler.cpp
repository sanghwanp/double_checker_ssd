#include "CommandBufferHandler.h"

void CommandBufferHandler::AddWrite(unsigned int lba, unsigned long long data) {}

void CommandBufferHandler::AddErase(unsigned int lba) {}

std::vector<CommandBufferEntry> CommandBufferHandler::Flush() {
    return std::vector<CommandBufferEntry>();
}
