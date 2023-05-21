#include "task2.h"

int64_t GCD(int64_t a, int64_t b) {
    while (b) {
        a %= b;
        std::swap (a, b);
    }
    return a;
}

// y = kx, 0 <= x <= r > 0
uint64_t GetUnderLine(int64_t k, int64_t r) {
    uint64_t points_under_line = static_cast<uint64_t >(r) * (r + 1) * k / 2;
    return points_under_line;
}

// y = Px/Q, x <= r
uint64_t GetOnLine(int64_t P, int64_t Q, int64_t r, int64_t gcd) {
    if (P == 0) {
        return static_cast<uint64_t>(r) + 1;
    } else {
        return 1 + std::floor(r * gcd / Q);
    }
}

// y = Px/Q, 0 <= x <= r > 0
uint64_t GetOnAndUnderLine(int64_t P, int64_t Q, int64_t r,
                           std::optional<int64_t> gcd = std::nullopt) {
    if (gcd == std::nullopt) {
        gcd = GCD(P, Q);
    }
    uint64_t points_on_line = GetOnLine(P, Q, r, *gcd);
    if (P % Q == 0) {
        int64_t k = P / Q;
        uint64_t points_under_line = GetUnderLine(k, r);
        return points_on_line + points_under_line;
    }

    uint64_t points_1_part = GetUnderLine((P - P % Q) / Q, r);

    int64_t new_r = std::floor(static_cast<double>(P % Q) * r / Q);
    uint64_t points_inverted = GetOnAndUnderLine(Q, P % Q,new_r, gcd);
    uint64_t area = static_cast<uint64_t>(new_r + 1) * (r + 1);

    uint64_t points_2_part = area - points_inverted;

    return points_1_part + points_2_part + points_on_line;
}

uint64_t GetOnAndUnderLine(int64_t P, int64_t Q, int64_t l, int64_t r) {
    assert (l <= r);
    if (l < 0 && r < 0) {
        int64_t new_l = -r, new_r = -l;
        return GetOnAndUnderLine(P, Q, new_l, new_r);
    }
    if (l < 0 && r == 0) {
        return GetOnAndUnderLine(P, Q, -l);
    }
    if (l < 0 && r > 0) {
        return GetOnAndUnderLine(P, Q, r) + GetOnAndUnderLine(P, Q, -l) - 1;
    }
    if (l == 0) {
        return GetOnAndUnderLine(P, Q, r);
    }
    if (l > 0 && r > 0) {
        return GetOnAndUnderLine(P, Q, r) - GetOnAndUnderLine(P, Q, l - 1);
    }
    assert(false);
}