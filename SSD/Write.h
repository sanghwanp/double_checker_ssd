#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>
typedef unsigned int uint;

const int MAX_LBA = 99;
const int MAX_DATA_LEN = 10;
const int MAX_SIZE = 100;
const int NAND_SIZE = sizeof(int) * (MAX_SIZE);
const std::string FILE_NAME = "ssd_nand.txt";

struct Command {
  int cmdType;
  int lba;
  uint data;

  std::string typeStr;
  std::string dataStr;

  Command() : cmdType{0}, lba{0}, data{0} {}
  Command(int t, int l, uint d) : cmdType{t}, lba{l}, data{d} {}

  bool CheckErrorCmd() {
    if (typeStr != "W") { // 입력된 string의 첫번째 글자를 확인하기
      return true;
    }
    if (lba < 0 || lba > MAX_LBA) {
      return true;
    }
    if (dataStr.length() > MAX_DATA_LEN) {
      return true;
    }
    if (!(dataStr[0] == '0' && dataStr[1] == 'x')) {
      return true;
    }
    for (int i = 2; i < dataStr.length(); i++) {
      if (std::isxdigit(dataStr[i])) continue;
      return true;
    }
    return false;
  }

  void Parse(std::string cmdStr) {
    std::istringstream iss(cmdStr);
    iss >> typeStr >> lba >> dataStr;

    if (CheckErrorCmd()) throw std::invalid_argument("Invalid command type");

    cmdType = 1;
    data = std::stoul(dataStr, nullptr, 16);
  }
};

class WriteCmd {
 public:

  void Init() {
    memset(nand, 0x0, NAND_SIZE);
  }

  void Run(Command cmd) {
    //nand[cmd.lba] = cmd.data;

    std::ifstream inFile(FILE_NAME);
    if (inFile.is_open()) {
      // 파일 읽기
      for (int i = 0; i < MAX_SIZE; ++i) {
        inFile >> nand[i];
      }
      inFile.close();

      std::cout << "파일에서 데이터 읽음" << std::endl;
    } else {
      std::cout << "파일이 존재하지 않아 새로 생성합니다." << std::endl;
      Init();
    }

    // 2. 새로운 데이터 이식
    SetData(cmd.lba, cmd.data);

    // 3. 파일에 저장
    std::ofstream outFile(FILE_NAME);
    if (!outFile.is_open()) {
      std::cerr << "파일 열기 실패" << std::endl;
      return;
    }

    for (int i = 0; i < MAX_SIZE; ++i) {
      outFile << "0x" << std::setfill('0') << std::setw(8) << std::hex
              << std::uppercase << nand[i] << std::endl;
    }
    outFile.close();
  }

  void SetData(int i, uint d) { nand[i] = d; }


  uint nand[MAX_LBA + 1];
  Command cmd;
};