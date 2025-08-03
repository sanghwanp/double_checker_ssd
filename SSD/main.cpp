#include <memory>

#include "CommandFactory.h"
#include "FileDriver.h"
#include "Parser.h"
#include "SSD.h"

int main(int argc, char* argv[]) {

  FileDriver* fileDriver = FileDriver::GetInstance();
  CommandFactory* commandFactory = CommandFactory::GetInstance();
  CommandBufferHandler* bufferHandler = CommandBufferHandler::GetInstance();

  SSD& ssd = SSD::GetInstance(fileDriver, bufferHandler, commandFactory);
  Parser parser;

  ssd.Run(parser.GetCommand(argc, argv));

  return 0;
}
