#pragma once

#include <cstdint>
#include <cmath>

namespace math {
    int64_t Ceil(double x);

    int64_t CeilQuotient(int64_t lhs, int64_t rhs);

    int64_t StrongCeil(double x);

    int64_t StrongCeilQuotient(int64_t lhs, int64_t rhs);

    int64_t Floor(double x);

    int64_t FloorQuotient(int64_t lhs, int64_t rhs);

    int64_t StrongFloor(double x);

    int64_t StrongFloorQuotient(int64_t lhs, int64_t rhs);
}