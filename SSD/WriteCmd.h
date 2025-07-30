#pragma once
#include <iostream>
#include <sstream>
typedef unsigned int uint;

const int MAX_DATA_LEN = 10;
const int MAX_SIZE = 100;
const int NAND_SIZE = sizeof(int) * (MAX_SIZE);

struct Command {
  int cmdType;
  int lba;
  uint data;

  std::string typeStr;
  std::string dataStr;

  Command() : cmdType{0}, lba{0}, data{0} {}
  Command(int t, int l, uint d) : cmdType{t}, lba{l}, data{d} {}

  bool CheckErrorCmd() {
    if (typeStr != "W") {  // �Էµ� string�� ù��° ���ڸ� Ȯ���ϱ�
      return true;
    }
    if (lba < 0 || lba >= MAX_SIZE) {
      return true;
    }
    if (dataStr.length() > MAX_DATA_LEN) {
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

  void Init();
  void Run(Command cmd);
  void SetData(int i, uint d);

  uint nand[MAX_SIZE];
  Command cmd;
};
