#include <iostream>
#include "SystemServices.hpp"
#include <cstring>
int main(int argc, char *argv[]) {
    std::cout << "iPassaHarte Started" << std::endl;

    for(int i=0;i<argc;i++){
        if(strcmp(argv[i], "-socket") == 0){
            std::cout << "OK\n";
        } else if(strcmp(argv[i], "-file") == 0){

        }
    }

    initializeSystem();

    return 0;
}
