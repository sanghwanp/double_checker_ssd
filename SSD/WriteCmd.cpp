#include "WriteCmd.h"

bool WriteCmd::CheckFirst() {
  std::ifstream inFile(FILE_NAME);
  return !(inFile.is_open());
}
void WriteCmd::Init() { memset(nand, 0x0, NAND_SIZE); }

void WriteCmd::Run(Command cmd) {

  // 1. Read File
  std::ifstream inFile(FILE_NAME);
  if (inFile.is_open()) {
    std::cout << "file exist" << std::endl;
    std::string hexStr;
    for (int idx = 0; idx < MAX_SIZE; ++idx) {
      inFile >> hexStr;
      nand[idx] = std::stoul(hexStr, nullptr, 16);
    }
    inFile.close();
  }

  // 2. Set Data
  SetData(cmd.lba, cmd.data);

  // 3. Store File
  std::ofstream outFile(FILE_NAME);
  if (!outFile.is_open()) {
    std::cerr << "making file error" << std::endl;
    return;
  }

  for (int idx = 0; idx < MAX_SIZE; ++idx) {
    outFile << "0x" << std::setfill('0') << std::setw(8) << std::hex
            << std::uppercase << nand[idx] << std::endl;
  }
  outFile.close();
}

void WriteCmd::SetData(int idx, uint d) { nand[idx] = d; }
