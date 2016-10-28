#pragma once

#include <chrono>

using namespace std;

long long get_time_shift_ms(chrono::time_point<chrono::steady_clock> start_time);