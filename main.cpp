#include "task2/task2.h"
#include "task2/tests/task2_tests.h"
#include <iostream>
#include <string>


int main(int argc, char* argv[]) {
    //MinTest(1000000, 10, 4, 4);
    //std::cout << FMinVal(-4, -1, 2, 3, 0, 3, RoundingFunction::kFloor);
    Task2HardTest(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]));
    return 0;
}
