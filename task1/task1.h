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
int64_t FMinVal(int64_t A, int64_t B, int64_t P, int64_t Q, int64_t l, int64_t r,
                RoundingFunction g);

std::pair<int64_t, int64_t> MinAPlusB(int64_t p, int64_t q);