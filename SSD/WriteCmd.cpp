#include "WriteCmd.h"

void WriteCmd::Init() { memset(nand, 0x0, NAND_SIZE); }

void WriteCmd::Run(Command cmd) {
  Init();
  SetData(cmd.lba, cmd.data);
}

void WriteCmd::SetData(int i, uint d) { nand[i] = d; }
