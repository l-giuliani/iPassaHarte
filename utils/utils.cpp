//
// Created by lgiuliani on 17/10/2020.
//

#include "utils.h"
#include <iostream>
#include <iomanip>
#include <string.h>
#include <chrono>

void printHexBinary(char* data, int len){
    for(int i=0; i<len; ++i) {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (unsigned int) (data[i] & 0xFF);
    }
}

std::string getActualTimestamp(){
    char buffer[50];
    memset(buffer,0,sizeof(buffer));

    time_t t = time(NULL);
    struct tm *lt = localtime(&t);

    sprintf(buffer, "%02d/%02d/%02d %02d:%02d:%02d", lt->tm_mday, lt->tm_mon+1, lt->tm_year%100, lt->tm_hour, lt->tm_min, lt->tm_sec);
    std::string datetime(buffer);
    return datetime;
}