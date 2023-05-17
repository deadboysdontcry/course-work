#pragma once
#include <cstdint>
#include <optional>
#include <cmath>

int64_t Gcd(int64_t a, int64_t b);

// y = Px/Q,  l <= x <= r
uint64_t GetOnAndUnderLine(int64_t P, int64_t Q, int64_t l, int64_t r);