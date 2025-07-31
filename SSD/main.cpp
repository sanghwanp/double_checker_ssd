#if (MAIN_SELECT == 1)
#include <iostream>
#include <stdexcept>
#include <fstream>

#include "ReadArguments.h"
#include "ReadCmd.h"
#include "SSD.h"
#include "WriteArguments.h"
#include "WriteCmd.h"

int main(int argc, char* argv[]) {
  try {
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++) {
      args.emplace_back(argv[i]);
    }
    // if (argc < 3) {
    //   throw std::invalid_argument("Usage: <R/W> <LBA> [Data]");
    // }
    if (args.size() <= 1 || args.size() >= 4) {
      throw std::invalid_argument("Usage1: R <LBA>\nUsage2: W <LBA> <Data>");
    }

    const std::string& cmdTypeStr = args[0];
    std::string argsStr;
    for (int i = 0; i < args.size(); i++) {
      argsStr += args[i];
      if (i != args.size() - 1) argsStr += " ";
    }
    SSD ssd;
    ReadCmd readCmd;
    WriteCmd writeCmd;

    ssd.SetReadCmd(&readCmd);
    ssd.SetWriteCmd(&writeCmd);

    if (cmdTypeStr == "R" || cmdTypeStr == "read") {
      ReadArguments readArgs;
      readArgs.Parse(argsStr);

      unsigned int result = ssd.Read(&readArgs);
      //std::cout << result << "\n";

    } else if (cmdTypeStr == "W" || cmdTypeStr == "write") {
      WriteArguments writeArgs;
      writeArgs.Parse(argsStr);

      ssd.Write(&writeArgs);
    } else {
      throw std::invalid_argument("Unknown command type");
    }

  } catch (const std::exception& e) {
    std::ofstream ofs;
    ofs.open("C:\\ssd_output.txt");
    ofs << "ERROR";
    ofs.close();
    // std::cout << "ERROR";
    return 1;
  }

  return 0;
}

#endif