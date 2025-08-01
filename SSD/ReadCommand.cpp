#include "ReadCommand.h"

#include <filesystem>
#include <fstream>
#include <iostream>

void ReadCommand::Execute(IParam* param) {
    auto* readParam = dynamic_cast<ReadParam*>(param);
    if (!readParam) return;
    FileDriver FD = FileDriver::GetInstance();

    FD.SaveFile(READ_OUTPUT_FILE_NAME, FD.GetBufferData(readParam->lba.val), 1);
}
