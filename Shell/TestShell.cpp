#include "TestShell.h"

#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

static std::vector<unsigned int> ssd(100);

static void write(int lba, unsigned int data) {
  ssd[lba] = data;
  std::cout << "[Write] Done\n";
}

static unsigned int read(int lba) {
  std::cout << "[Read] LBA " << std::setw(2) << std::setfill('0') << std::dec
            << lba << " : 0x" << std::setw(8) << std::uppercase << std::hex
            << ssd[lba] << std::endl;
  return ssd[lba];
}

static void fullwrite(unsigned int data) {
  std::fill(ssd.begin(), ssd.end(), data);
  std::cout << "[Fullwrite] Done\n";
}

static void fullread() {
  for (int lba = 0; lba < 100; ++lba) {
    std::cout << "[Fullread] LBA " << std::setw(2) << std::setfill('0')
              << std::dec << lba << " : 0x" << std::setw(8) << std::uppercase
              << std::hex << ssd[lba] << std::endl;
  }
}

static void ts1() {
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

static void ts2() {
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

static void ts3() {
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

int TestShell::Exec(void) {
  std::string command;
  std::fill(ssd.begin(), ssd.end(), 0);

  while (true) {
    std::cout << "Shell> ";
    std::getline(std::cin, command);

    int eCmd = parseAndExecCommand(command);
    if (eCmd == eExitCmd) break;
  }
  return 0;
}

int TestShell::parseAndExecCommand(std::string command) {
  IParam* parsedCommand = parser.Parse(command);
  int eCmd = parsedCommand->eCmd;

  switch (eCmd) {
    case eWriteCmd: {
      WriteParam* writeCmd = dynamic_cast<WriteParam*>(parsedCommand);
      write(stoi(writeCmd->lba), stoul(writeCmd->data, nullptr, 16));
      break;
    }
    case eReadCmd: {
      ReadParam* readCmd = dynamic_cast<ReadParam*>(parsedCommand);
      read(stoi(readCmd->lba));
      break;
    }
    case eHelpCmd: {
      break;
    }
    case eExitCmd: {
      std::cout << "Shutting down" << std::endl;
      break;
    }
    case eFullwrite: {
      FullWriteParam* fwCmd = dynamic_cast<FullWriteParam*>(parsedCommand);
      fullwrite(stoul(fwCmd->data, nullptr, 16));
      break;
    }
    case eFullread: {
      fullread();
      break;
    }
    case eScriptCmd: {
      ScriptParam* scriptCmd = dynamic_cast<ScriptParam*>(parsedCommand);
      switch (scriptCmd->nScriptNumber) {
        case 1:
          ts1();
          break;
        case 2:
          ts2();
          break;
        case 3:
          ts3();
          break;
        default:
          break;
      }
      break;
    }
    case eInvalidCmd:
    default: {
      std::cout << "INVALID COMMAND" << std::endl;
      break;
    }
  }
  return eCmd;
}