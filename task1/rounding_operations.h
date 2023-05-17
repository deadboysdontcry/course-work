#pragma once

#include <cstdint>
#include <cmath>

namespace math {
    int64_t Ceil(double x);

    int64_t CeilQuotient(int64_t lhs, int64_t rhs);

    int64_t Loft(double x);

    int64_t LoftQuotient(int64_t lhs, int64_t rhs);

    int64_t Floor(double x);

    int64_t FloorQuotient(int64_t lhs, int64_t rhs);

    int64_t Cellar(double x);

    int64_t CellarQuotient(int64_t lhs, int64_t rhs);
}