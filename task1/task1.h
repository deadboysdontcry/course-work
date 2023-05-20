#pragma once


#include <cstdint>
#include <cassert>
#include <utility>
#include <algorithm>
#include <functional>
#include "rounding_operations.h"




enum RoundingFunction : uint8_t {
    kCeil = 0,
    kLoft = 1,
    kFloor = 2,
    kCellar = 3,
};

static_assert(RoundingFunction::kCeil == 0);
static_assert(RoundingFunction::kLoft == 1);
static_assert(RoundingFunction::kFloor == 2);
static_assert(RoundingFunction::kCellar == 3);
const std::array<std::function<__int128_t(__int128_t, __int128_t)>, 4> typeToDivFunc{
        math::CeilQuotient, math::LoftQuotient, math::FloorQuotient, math::CellarQuotient};


// f(x) = Ax + Bg( Px / Q), x in [l, l + 1, ..., r], Q != 0
__int128_t FMinVal(__int128_t A, __int128_t B, __int128_t P, __int128_t Q, __int128_t l, __int128_t r,
                RoundingFunction g);

std::pair<int64_t, int64_t> MinAPlusB(int64_t p, int64_t q);