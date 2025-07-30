#include "WriteCmd.h"

bool WriteCmd::CheckFirst() { return true; }
void WriteCmd::Init() { memset(nand, 0x0, NAND_SIZE); }

void WriteCmd::Run(Command cmd) {
  if (CheckFirst()) {
    std::cout << "make new file" << std::endl;
    Init();
  } else {
    std::cout << "file exist" << std::endl;
  }

  SetData(cmd.lba, cmd.data);
}

void WriteCmd::SetData(int i, uint d) { nand[i] = d; }
