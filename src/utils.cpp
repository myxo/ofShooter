#include "utils.h"

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


// TODO make config file json
unordered_map<string, string> parse_config_file(const char* filename){
    unordered_map<string, string> table;
    ifstream f(filename);
    if (!f.is_open()){
        std::cout << "ERROR: parse_config_file, file | " << filename << " | cannot be open\n";
    }
    string line;

    while(getline(f, line)){
        std::istringstream iss(line);
        string key, value;
        if (! (iss >> key >> value)){ break; }

        table[key] = value;
    }
    return table;
}