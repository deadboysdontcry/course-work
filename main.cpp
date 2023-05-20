#include "task2/task2.h"
#include "task2/tests/task2_tests.h"
#include "task1/tests/task1_tests.h"
#include "task1/task1.h"
#include <iostream>
#include <string>


int main(int argc, char* argv[]) {
    MinTest(1000000000, 100000000, 100000000, 200);
    //std::cout << FMinVal(4, -4, 1, 4, 1, 3, RoundingFunction::kFloor);
   // Task2HardTest(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]));
    return 0;
}
