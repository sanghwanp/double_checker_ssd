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

static void ts2() {
  /*
  Loop는 30회
  1. 4번 LBA에 값을적는다.
  2. 0번 LBA에 같은 값을 적는다.
  3. 3번 LBA에 같은 값을 적는다.
  4. 1번 LBA에 같은 값을 적는다.
  5. 2번 LBA에 같은 값을 적는다.
  6. LBA 0 ~4번, ReadCompare
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
  std::cout << "PASS" << std::endl;
}

static void ts3() {
  /*
  Loop 200회
  1. 0번 LBA에 랜덤값을 적는다.
  2. 99번 LBA에 랜덤값을 적는다.
  3. LBA 0번과 99번, ReadCompare를 수행
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
  std::cout << "PASS" << std::endl;
}

int TestShell::Exec(void) {
  std::fill(ssd.begin(), ssd.end(), 0);
  std::string command;

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
      std::vector<std::string> program = {"write", writeCmd->lba,
                                          writeCmd->data};
      commandWrite.Call(program);
      break;
    }
    case eReadCmd: {
      ReadParam* readCmd = dynamic_cast<ReadParam*>(parsedCommand);
      std::vector<std::string> program = {"read", readCmd->lba};
      commandRead.Call(program);
      break;
    }
    case eHelpCmd: {
      std::vector<std::string> program = {"help"};
      commandHelp.Call(program);
      break;
    }
    case eExitCmd: {
      std::vector<std::string> program = {"exit"};
      commandExit.Call(program);
      break;
    }
    case eFullwrite: {
      FullWriteParam* fwCmd = dynamic_cast<FullWriteParam*>(parsedCommand);
      std::vector<std::string> program = {"fullwrite", fwCmd->data};
      commandFullWrite.Call(program);
      break;
    }
    case eFullread: {
      std::vector<std::string> program = {"fullread"};
      commandFullRead.Call(program);
      break;
    }
    case eEraseCmd: {
      EraseParam* eraseCmd = dynamic_cast<EraseParam*>(parsedCommand);
      std::vector<std::string> program = {"erase", eraseCmd->lba, eraseCmd->size};
      commandErase.Call(program);
      break;
    }
    case eFlushCmd: {
      std::vector<std::string> program = {"flush"};
      commandFlush.Call(program);
      break;
    }
    case eScriptCmd: {
      ScriptParam* scriptCmd = dynamic_cast<ScriptParam*>(parsedCommand);
      switch (scriptCmd->nScriptNumber) {
        case 1:
          commandTestScript.Call(*parsedCommand);
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
