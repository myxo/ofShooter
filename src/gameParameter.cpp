#include "gameParameter.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <exception> 

// TODO make config file json
void GameParameter::parse_config_file(const char* filename){
    ifstream f(filename);
    if (!f.is_open()){
        // std::cout << "ERROR: parse_config_file, file | " << filename << " | cannot be open\n";
        throw std::invalid_argument("ERROR: parse_config_file");
    }

    string line;
    while(getline(f, line)){
        std::istringstream iss(line);
        string key, value;
        if (! (iss >> key >> value)){ break; }

        if (params.count(key) != 0){
            throw string("ERROR: several identical key in game parameters file");
        }
        params[key] = value;
    }
}

// may throw exception!
int GameParameter::getInt(string name){
    return stoi(params.at(name));
}

double GameParameter::getDouble(string name){
    return stod(params.at(name));
}

string GameParameter::getString(string name){
    return params.at(name);
}