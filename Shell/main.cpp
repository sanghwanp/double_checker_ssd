#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#if (MAIN_SELECT == 3)
std::vector<unsigned int> ssd(100);

void write(int lba, unsigned int data) {
  ssd[lba] = data;
  std::cout << "[Write] Done\n";
}

void read(int lba) {
  std::cout << "[Read] LBA " << std::setw(2) << std::setfill('0') << std::dec
            << lba << " : 0x" << std::setw(8) << std::uppercase << std::hex
            << ssd[lba] << std::endl;
}

void fullwrite(unsigned int data) {
  std::fill(ssd.begin(), ssd.end(), data);
  std::cout << "[Fullwrite] Done\n";
}

void fullread() {
  for (int lba = 0; lba < 100; ++lba) {
    std::cout << "[Fullread] LBA " << std::setw(2) << std::setfill('0')
              << std::dec << lba << " : 0x" << std::setw(8) << std::uppercase
              << std::hex << ssd[lba] << std::endl;
  }
}

void ts1() {}

void ts2() {}

void ts3() {}

int main() {
  std::string command;
  std::string lba;
  std::string data;

  std::fill(ssd.begin(), ssd.end(), 0);

  while (true) {
    std::cout << "Shell> ";
    std::cin >> command;
    if (command == "exit") {
      std::cout << "Shutting down\n";
      break;
    } else if (command == "write") {
      std::cin >> lba;
      std::cin >> data;
      write(stoi(lba), stoul(data, nullptr, 16));
    } else if (command == "read") {
      std::cin >> lba;
      read(stoi(lba));
    } else if (command == "fullwrite") {
      std::cin >> data;
      fullwrite(stoul(data, nullptr, 16));
    } else if (command == "fullread") {
      fullread();
    } else if (command == "1_" || command == "1_FullWriteAndReadCompare") {
      ts1();
    } else if (command == "2_" || command == "2_PartialLBAWrite") {
      ts2();
    } else if (command == "3_" || command == "3_WriteReadAging") {
      ts3();
    } else {
      std::cout << "INVALID COMMAND" << std::endl;
    }
  }

  return 0;
}
#endif