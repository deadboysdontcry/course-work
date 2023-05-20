#include "task1_tests.h"
#include "../task1.h"

#include <vector>
#include <cstdint>
#include <iostream>
#include <cstdint>

namespace APlusBMin {
    struct TestCase {
        int64_t p, q;
    };

    std::ostream& operator<<(std::ostream& out, const TestCase& t) {
        out << t.p << " " << t.q;
        return out;
    }

    std::pair<int64_t, int64_t> HardSolve(TestCase t) {
        int64_t cur_min_sum = std::numeric_limits<int64_t>::max(), ans_a = -11, ans_b = -1;
        for (int64_t a = 0; a < t.p; a++) {
            for (int64_t b = 1; b < t.p; b++) {
                if (b * t.q % t.p == a) {
                    if (a + b < cur_min_sum) {
                        cur_min_sum = a + b;
                        ans_a = a;
                        ans_b = b;
                    }
                }
            }
        }
        return {ans_a, ans_b};
    }

    TestCase GenerateTest(std::vector<int64_t> p_pool) {
        int64_t p = p_pool[rand() % p_pool.size()];
        int64_t q = rand() % p;
        return TestCase{p, q};
    }

    bool IsOk(TestCase t) {
        auto expected = HardSolve(t), actual = MinAPlusB(t.p, t.q);
        if (expected.first + expected.second != actual.first + actual.second) {
            return false;
        }
        return true;
    }

    void StressTest(int num_iter, int64_t max_p) {
        std::vector<int64_t> lp(max_p);
        std::vector<int64_t> p_pool;

        for (int i=2; i<=max_p; ++i) {
            if (lp[i] == 0) {
                lp[i] = i;
                p_pool.push_back (i);
            }
            for (int j=0; j<(int)p_pool.size() && p_pool[j]<=lp[i] && i*p_pool[j]<=max_p; ++j)
                lp[i * p_pool[j]] = p_pool[j];
        }
        for (int i = 0; i < num_iter; ++i) {
            auto t = GenerateTest(p_pool);
            if (!IsOk(t)) {
                std::cout << t.p << " " << t.q << "\n";
                std::cout << HardSolve(t).first << " " << HardSolve(t).second << " vs " << MinAPlusB(t.p, t.q).first << " " << MinAPlusB(t.p, t.q).second << std::endl;
                return;
            }
        }
    }
}
