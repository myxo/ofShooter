// #include "utils.h"

// #include <unordered_map>
// #include <iostream>
// #include <fstream>
// #include <string>
// #include <sstream>

#include <chrono>
using namespace std;



// unordered_map<string, string> parse_config_file(const char* filename){
    
// }

long long get_time_shift_ms(chrono::time_point<chrono::steady_clock> start_time){
    return std::chrono::duration_cast<chrono::milliseconds>
            (chrono::steady_clock::now() - start_time).count();
}