#include "rounding_operations.h"


namespace math {
    int64_t Ceil(double x) {
        return std::ceil(x);
    }

    int64_t CeilQuotient(int64_t lhs, int64_t rhs) {
        return Ceil(static_cast<double>(lhs) / rhs);
    }

    int64_t StrongCeil(double x) {
        int64_t cur = Ceil(x);
        if (static_cast<double>(cur) == x) {
            return cur + 1;
        }
        return cur;
    }

    int64_t StrongCeilQuotient(int64_t lhs, int64_t rhs) {
        return StrongCeil(static_cast<double>(lhs) / rhs);
    }

    int64_t Floor(double x) {
        return std::floor(x);
    }

    int64_t FloorQuotient(int64_t lhs, int64_t rhs) {
        return Floor(static_cast<double>(lhs) / rhs);
    }

    int64_t StrongFloor(double x) {
        int64_t cur = Floor(x);
        if (static_cast<double>(cur) == x) {
            return cur - 1;
        }
        return cur;
    }

    int64_t StrongFloorQuotient(int64_t lhs, int64_t rhs) {
        return StrongFloor(static_cast<double>(lhs) / rhs);
    }

}
