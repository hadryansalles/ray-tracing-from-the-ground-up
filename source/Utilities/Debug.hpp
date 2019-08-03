#pragma once

#include <string>
#include <iostream>

#define DEBUG false

inline void debug_print(const char* s){
    if(DEBUG){
        std::cout << s;
    }
}