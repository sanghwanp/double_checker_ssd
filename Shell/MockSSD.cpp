#include "MockSSD.h"

void MockSSD::SSDWrite(int lba, const string& value) {}

string MockSSD::SSDRead(int lba) { return ""; }