#pragma once
#include <string>
#include <vector>

#include "SSDInterface.h"
using std::vector;

int CommandWrite(SSDInterface& ssd, const vector<std::string>& tokens);
bool IsInvalidLBA(int lba);
bool IsInvalidValue(const string& value);
