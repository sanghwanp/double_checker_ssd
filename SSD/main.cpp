#include <memory>

#include "CommandFactory.h"
#include "FileDriver.h"
#include "Parser.h"
#include "SSD.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

  FileDriver* fileDriver = FileDriver::GetInstance();
  CommandFactory* commandFactory = CommandFactory::GetInstance();
  CommandBufferHandler* bufferHandler = CommandBufferHandler::GetInstance();

  SSD& ssd = SSD::GetInstance(fileDriver, bufferHandler, commandFactory);

  Parser parser;

  cout << &parser << endl;
  cout << argc << endl;
  cout << argv << endl;
  ssd.Run(parser.GetParam(argc, argv));

  return 0;
}
