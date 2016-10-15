#pragma once

#include <unordered_map>

using namespace std;

unordered_map<string, string> parse_config_file(const char* filename);