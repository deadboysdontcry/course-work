#include "task2/task2.h"
#include "task2/tests/task2_tests.h"
#include "task1/tests/task1_tests.h"
#include "task1/task1.h"
#include <iostream>
#include <string>
#include <fstream>


int main(int argc, char* argv[]) {
   APlusBMin::StressTest(1000000, 10000);
   //auto a = MinAPlusB(2, 1);
   //std::cout << a.first << " " << a.second << std::endl;
   //FMinTests::StressTest(1000000, 50000, 500000, 20000000);
  // auto x = FMinVal(-2, 1, 1, 3, 2, 3, RoundingFunction::kFloor);
  // std::cout << x;
   return 0;
}
