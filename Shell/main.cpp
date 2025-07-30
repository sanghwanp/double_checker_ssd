#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <random>

#if (MAIN_SELECT == 3)
std::vector<unsigned int> ssd(100);

void write(int lba, unsigned int data) {
  ssd[lba] = data;
  std::cout << "[Write] Done\n";
}

unsigned int read(int lba) {
  std::cout << "[Read] LBA " << std::setw(2) << std::setfill('0') << std::dec
            << lba << " : 0x" << std::setw(8) << std::uppercase << std::hex
            << ssd[lba] << std::endl;
  return ssd[lba];
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

void ts1() {
  /*
  1. 0 ~ 4�� LBA���� Write ��ɾ �����Ѵ�
  2. 0 ~ 4�� LBA���� ReadCompare ����
  3. 5 ~ 9�� LBA���� �ٸ� ������Write ��ɾ �����Ѵ�
  4. 5 ~ 9�� LBA���� ReadCompare ����
  5. 10 ~ 14�� LBA���� �ٸ� ������ Write ��ɾ �����Ѵ�.
  6. 10 ~ 14�� LBA���� ReadCompare ����
  7. ���Ͱ�����Ģ������ü����������Full Write + Read Compare�� �����Ѵ�
  */
  unsigned int data;
  for (int idx = 0; idx < 100; idx += 5) {
    data = idx;
    write(idx + 0, data);
    write(idx + 1, data);
    write(idx + 2, data);
    write(idx + 3, data);
    write(idx + 4, data);
    if (data != read(idx + 0)) {
      std::cout << "FAIL" << std::endl;
      return;
    }
    if (data != read(idx + 1)) {
      std::cout << "FAIL" << std::endl;
      return;
    }
    if (data != read(idx + 2)) {
      std::cout << "FAIL" << std::endl;
      return;
    }
    if (data != read(idx + 3)) {
      std::cout << "FAIL" << std::endl;
      return;
    }
    if (data != read(idx + 4)) {
      std::cout << "FAIL" << std::endl;
      return;
    }
  }
}

void ts2() {
  /*
  Loop�� 30ȸ
  1. 4�� LBA�� �������´�.
  2. 0�� LBA�� ���� ���� ���´�.
  3. 3�� LBA�� ���� ���� ���´�.
  4. 1�� LBA�� ���� ���� ���´�.
  5. 2�� LBA�� ���� ���� ���´�.
  6. LBA 0 ~4��, ReadCompare
*/
  unsigned int data;
  for (int idx = 0; idx < 30; ++idx) {
    data = idx;
    write(4, data);
    write(0, data);
    write(3, data);
    write(1, data);
    write(2, data);
    if (data != read(0)) {
      std::cout << "FAIL" << std::endl;
      return;
    }
    if (data != read(1)) {
      std::cout << "FAIL" << std::endl;
      return;
    }
    if (data != read(2)) {
      std::cout << "FAIL" << std::endl;
      return;
    }
    if (data != read(3)) {
      std::cout << "FAIL" << std::endl;
      return;
    }
    if (data != read(4)) {
      std::cout << "FAIL" << std::endl;
      return;
    }
  }
}

void ts3() {
  /*
  Loop 200ȸ
  1. 0�� LBA�� �������� ���´�.
  2. 99�� LBA�� �������� ���´�.
  3. LBA 0���� 99��, ReadCompare�� ����
 */

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<unsigned int> distrib(0, 0xffffffff);
  unsigned int data;

  for (int idx = 0; idx < 200; ++idx) {
    data = distrib(gen);
    write(0, data);
    write(99, data);

    if (data != read(0)) {
      std::cout << "FAIL" << std::endl;
      return;
    }
    if (data != read(99)) {
      std::cout << "FAIL" << std::endl;
      return;
    }
  }
}

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