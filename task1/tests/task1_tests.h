#pragma once

#include <cstdint>

namespace FMinTests {
    void StressTest(int num_iter, __int128_t max_ab, __int128_t max_pq, __int128_t max_lr);
}

namespace APlusBMin {
    void StressTest(int num_iter, int64_t max_p);
}