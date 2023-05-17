#pragma once

#include "../task2.h"

#include <iostream>
#include <cstdint>
#include <random>

uint64_t HardSolve(int64_t P, int64_t Q, int l, int64_t r) {
    uint64_t cnt = 0;
    for (int i = l; i <= r; ++i) {
        auto ii = std::abs(i);
        uint64_t top = static_cast<uint64_t>(ii) * P / Q;
        cnt += top + 1;
    }
    return cnt;
}

void Task2HardTest(int num_it, int maxpq, int maxrl) {
    for (int i = 0; i < num_it; ++i) {
        int p = rand() % maxpq; int q = rand() % maxpq + 1; int r = rand() % maxrl, l = rand() % maxrl;
        int rand1 = rand() % 2;
        if (rand1) {
            r = -r;
        }
        rand1 = rand() % 2;
        if (rand1) {
            l = -l;
        }
        if (l > r) {
            std::swap(l, r);
        }
        uint64_t expected = HardSolve(p, q,l, r), actual = GetOnAndUnderLine(p, q,l, r);
        if (expected != actual) {
            std::cout << p << " " << q << " " << l << " " << r << std::endl;
            std::cout << expected << " " << actual << std::endl;
        }
    }
}
