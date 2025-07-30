#include "WriteCmd.h"

void WriteCmd::Run(IArguments* args) {
  auto writeArgs = dynamic_cast<WriteArguments*>(args);
  if (!writeArgs) {
    throw std::invalid_argument("Invalid argument type for WriteCmd");
  }

  LoadFromFile();                                      // 파일 읽기
  SetData(writeArgs->GetLba(), writeArgs->GetData());  // 데이터 설정
  SaveToFile();                                        // 파일에 저장
}

bool WriteCmd::CheckFirst() {
  std::ifstream inFile(FILE_NAME);
  return !inFile.is_open();
}

void WriteCmd::Init() { memset(nand, 0x0, sizeof(nand)); }

void WriteCmd::SetData(int idx, unsigned int data) { nand[idx] = data; }

unsigned int WriteCmd::GetData(int idx) const { return nand[idx]; }

void WriteCmd::LoadFromFile() {
  std::ifstream inFile(FILE_NAME);
  if (inFile.is_open()) {
    std::string hexStr;
    for (int idx = 0; idx < MAX_LBA_SIZE; ++idx) {
      inFile >> std::hex >> nand[idx];
    }
    inFile.close();
  } else {
    Init();  // 파일이 없으면 초기화
  }
}

void WriteCmd::SaveToFile() {
  std::ofstream outFile(FILE_NAME);
  if (!outFile.is_open()) {
    throw std::runtime_error("Failed to open SSD file for writing");
  }

  for (int idx = 0; idx < MAX_LBA_SIZE; ++idx) {
    outFile << std::hex << nand[idx] << "\n";
  }
  outFile.close();
}
