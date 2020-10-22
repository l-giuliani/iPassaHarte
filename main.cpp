#include <iostream>
#include "SystemServices.hpp"

int main(int argc, char *argv[]) {
    std::cout << "iPassaHarte Started" << std::endl;

    SystemService::initializeSystem(argc, argv);

    return 0;
}
