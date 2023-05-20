#pragma once


#include <cstdint>
#include <cassert>
#include <utility>
#include <algorithm>
#include <functional>
#include "rounding_operations.h"


const std::array<std::function<__int128_t(__int128_t, __int128_t)>, 4> typeToDivFunc{
        math::CeilQuotient, math::LoftQuotient, math::FloorQuotient, math::CellarQuotient};

enum RoundingFunction : uint8_t {
    kCeil = 0,
    kLoft = 1,
    kFloor = 2,
    kCellar = 3,
};

// f(x) = Ax + Bg( Px / Q), x in [l, l + 1, ..., r], Q != 0
__int128_t FMinVal(__int128_t A, __int128_t B, __int128_t P, __int128_t Q, __int128_t l, __int128_t r,
                RoundingFunction g);