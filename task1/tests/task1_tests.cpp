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

int64_t MinHardSolve(int64_t A, int64_t B, int64_t P, int64_t Q, int64_t l, int64_t r, RoundingFunction g) {
    int64_t min_val = std::numeric_limits<int64_t>::max();
    for (auto i = l; i <= r; ++i) {
        int64_t func_value = A * i + B * typeToDivFunc[g](i * P, Q);
        min_val = std::min(min_val, func_value);
    }
    return min_val;
}

int64_t MinExpected(TestCase t) {
    return MinHardSolve(t.A, t.B, t.P, t.Q, t.l, t.r, t.g);
}

int64_t MinActual(TestCase t) {
    return FMinVal(t.A, t.B, t.P, t.Q, t.l, t.r, t.g);
}

int64_t MaybeNeg(int64_t x) {
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
        std::cout << expected << " vs " << actual << std::endl;
        return false;
    }
    return true;
}

void MinTest(int num_iter, int64_t max_ab, int64_t max_pq, int64_t max_lr) {
    for (int i = 0; i < num_iter; ++i) {
        auto t = GenerateTest(max_ab, max_pq, max_lr);
        if (!MinCheck(t)) {
            std::cout << "OK is " << i << " cases;\n you tried your best!!!!!!" << std::endl;
            return;
        }
    }
}