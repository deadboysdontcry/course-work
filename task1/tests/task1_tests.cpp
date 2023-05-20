#include "task1_tests.h"

#include "../task1.h"
#include <cstdint>
#include <random>
#include <iostream>


struct TestCase {
    int64_t A, B, P, Q, l, r;
    RoundingFunction g;
};

std::string GToString(RoundingFunction g) {
    switch (g) {

        case kCeil:
            return "ceil";
        case kLoft:
            return "loft";
        case kFloor:
            return "floor";
        case kCellar:
            return "cellar";
    }
}

std::ostream& operator<<(std::ostream& os, TestCase t) {
    os << t.A << "x + " << "( " << t.B << GToString(t.g) << "(" << t.P << "x/" << t.Q << ") )" << std::endl;
    os << "[" << t.l << ", ..., " << t.r << "]";
    return os;
}

__int128_t MinHardSolve(__int128_t A, __int128_t B, __int128_t P, __int128_t Q, __int128_t l, __int128_t r, RoundingFunction g) {
    __int128_t min_val = std::numeric_limits<__int128_t>::max();
    for (auto i = l; i <= r; ++i) {
        __int128_t func_value = A * i + B * typeToDivFunc[g](i * P, Q);
        min_val = std::min(min_val, func_value);
    }
    return min_val;
}

__int128_t MinExpected(TestCase t) {
    return MinHardSolve(t.A, t.B, t.P, t.Q, t.l, t.r, t.g);
}

__int128_t MinActual(TestCase t) {
    return FMinVal(t.A, t.B, t.P, t.Q, t.l, t.r, t.g);
}

__int128_t MaybeNeg(__int128_t x) {
    int r = rand() % 2;
    if (r) {
        return x;
    }
    return -x;
}

TestCase GenerateTest(int64_t max_ab, int64_t max_pq, int64_t max_lr) {
    auto A = rand() % max_ab, B = rand() % max_ab, P = rand() % max_pq, Q = rand() % max_pq + 1,
            l = rand() % max_lr, r = rand() % max_lr;
    A = MaybeNeg(A);
    B = MaybeNeg(B);
    if (l > r) {
        std::swap(l, r);
    }
    return TestCase{A, B, P, Q, l, r, RoundingFunction(rand() % 4)};
}

bool MinCheck(TestCase t) {
    auto expected = MinExpected(t), actual = MinActual(t);
    if (expected != actual) {
        std::cout << t << std::endl;
        std::cout << static_cast<long double>(expected) << " vs " << static_cast<long double>(actual) << std::endl;
        return false;
    }
    return true;
}

void MinTest(int num_iter, __int128_t max_ab, __int128_t max_pq, __int128_t max_lr) {
    for (int i = 0; i < num_iter; ++i) {
        auto t = GenerateTest(max_ab, max_pq, max_lr);
        // std::cout << t << std::endl;
        if (!MinCheck(t)) {
            std::cout << "OK is " << i << " cases;\n you tried your best!!!!!!" << std::endl;
            return;
        }
       // std::cout << i + 1 << std::endl;
    }
}