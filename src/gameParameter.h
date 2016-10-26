#pragma once

#include <string>
#include <unordered_map>


using namespace std;

class GameParameter{
public:
    int getInt(string name);
    double getDouble(string name);
    string getString(string name);

    void parse_config_file(const char* filename);
private:
    unordered_map<string, string> params;
};