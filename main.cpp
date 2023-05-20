#include "task2/task2.h"
#include "task2/tests/task2_tests.h"
#include "task1/tests/task1_tests.h"
#include "task1/task1.h"
#include <iostream>
#include <string>
#include <fstream>


int main(int argc, char* argv[]) {
   //APlusBMin::StressTest(10000, 20);
   auto a = MinAPlusB(2, 1);
   std::cout << a.first << " " << a.second << std::endl;
   return 0;
}
