#include "ReadCmd.h"

unsigned int ReadCmd::Run(int lba, const std::vector<unsigned int> &storage) {
  return storage[lba];
}
