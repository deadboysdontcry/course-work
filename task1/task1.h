#pragma once


#include <cstdint>
#include <cassert>
#include <utility>
#include <algorithm>
#include <functional>
#include "rounding_operations.h"


const std::array<std::function<int64_t(int64_t, int64_t)>, 4> typeToDivFunc{
        math::CeilQuotient, math::LoftQuotient, math::FloorQuotient, math::CellarQuotient};

enum RoundingFunction : uint8_t {
    kCeil = 0,
    kLoft = 1,
    kFloor = 2,
    kCellar = 3,
};

std::pair<int, int> FindMinAplusB(int64_t p, int64_t q);


// f(x) = Ax + Bg( Px / Q), x in [l, l + 1, ..., r], Q != 0
int64_t FMinVal(int64_t A, int64_t B, int64_t P, int64_t Q, int64_t l, int64_t r, RoundingFunction g,
                int64_t prev_l = std::numeric_limits<int64_t>::min(), int64_t prev_r = std::numeric_limits<int64_t>::max());