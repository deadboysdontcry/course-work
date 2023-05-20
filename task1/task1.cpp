#include "task1.h"

// f(x) = Ax + Bg( Px / Q), x in [l, l + 1, ..., r], Q != 0
int64_t FMinVal(int64_t A, int64_t B, int64_t P, int64_t Q, int64_t l, int64_t r,
                RoundingFunction g) {
    if (l > r) {
        return 1e18;
    }

    if (l == r) {
        return l;
    }
    if (B == 0) {
        if (A > 0) {
            return l;
        }
        return r;
    }
    if (P % Q == 0) {
        const __int128_t l_result = static_cast<__int128_t>(A) * l + static_cast<__int128_t>(B) * typeToDivFunc[g](P * l, Q),
                      r_result = static_cast<__int128_t>(A) * r + static_cast<__int128_t>(B) * typeToDivFunc[g](P * r, Q);
        if (l_result < r_result) {
            return l;
        }
        return r;
    }

    const int64_t k = P / Q;

    const int64_t A_new = B, B_new = A + B * k,
                Q_new = P % Q, P_new = Q;
    int64_t l_new = typeToDivFunc[g](Q_new * l, Q), r_new = typeToDivFunc[g](Q_new * r, Q);

    const __int128_t l_val = B_new * l + B * l_new, r_val = B_new * r + B * r_new;
    __int128_t m_val = 1e36;
    int64_t mid;
    switch (g) {
        case RoundingFunction::kFloor: {
            if (B_new < 0) {
                {
                    const auto first = math::CellarQuotient(P_new * (l_new + 1), Q_new),
                         second = math::CellarQuotient(P_new * (r_new + 1), Q_new);
                    if (first < l) {
                        l_new++;
                    }
                    if (second > r) {
                        r_new--;
                    }
                }
                mid = FMinVal(A_new, B_new, P_new, Q_new, // -A_new
                               l_new + 1, r_new + 1, RoundingFunction::kCellar);
                mid = mid == 1e18 ? mid : math::CellarQuotient(mid * P_new, Q_new);
                m_val = mid == 1e18 ? mid : static_cast<__int128_t>(B_new) * mid + static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
            } else {
                {
                    const auto first = math::CeilQuotient(P_new * l_new, Q_new),
                            second = math::CeilQuotient(P_new * r_new, Q_new);
                    if (first < l) {
                        l_new++;
                    }
                    if (second > r) {
                        r_new--;
                    }
                }
                mid = FMinVal(A_new, B_new, P_new, Q_new,
                                                           l_new, r_new, RoundingFunction::kCeil);
                mid = mid == 1e18 ? mid : math::CeilQuotient(mid * P_new, Q_new);
                m_val = mid == 1e18 ? mid : static_cast<__int128_t>(B_new) * mid + static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
            }
        }
        break;
        case RoundingFunction::kCeil: {
            if (B_new < 0) {
                {
                    const auto first = math::FloorQuotient(P_new * l_new, Q_new),
                            second = math::FloorQuotient(P_new * r_new, Q_new);
                    if (first < l) {
                        l_new++;
                    }
                    if (second > r) {
                        r_new--;
                    }
                }
                mid = FMinVal(A_new, B_new, P_new, Q_new,
                                                           l_new, r_new, RoundingFunction::kFloor);
                mid = mid == 1e18 ? mid : math::FloorQuotient(mid * P_new, Q_new);
                m_val = mid == 1e18 ? mid : static_cast<__int128_t>(B_new) * mid + static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
            } else {
                {
                    const auto first = math::LoftQuotient(P_new * (l_new - 1), Q_new),
                            second = math::LoftQuotient(P_new * (r_new - 1), Q_new);
                    if (first < l) {
                        l_new++;
                    }
                    if (second > r) {
                        r_new--;
                    }
                }
                mid = FMinVal(A_new, B_new, P_new, Q_new,
                               l_new - 1, r_new - 1, RoundingFunction::kLoft);
                mid = mid == 1e18 ? mid : math::LoftQuotient(mid * P_new, Q_new);
                m_val = mid == 1e18 ? mid : static_cast<__int128_t>(B_new) * mid + static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
            }
        }
        break;
        case RoundingFunction::kLoft: {
            if (B_new < 0) {
                {
                    const auto first = math::CellarQuotient(P_new * l_new, Q_new),
                            second = math::CellarQuotient(P_new * r_new, Q_new);
                    if (first < l) {
                        l_new++;
                    }
                    if (second > r) {
                        r_new--;
                    }
                }
                mid = FMinVal(A_new, B_new, P_new, Q_new,
                                                           l_new, r_new, RoundingFunction::kCellar);
                mid = mid == 1e18 ? mid : math::CellarQuotient(mid * P_new, Q_new);
                m_val = mid == 1e18 ? mid : static_cast<__int128_t>(B_new) * mid + static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
            } else {
                {
                    const auto first = math::CeilQuotient(P_new * (l_new - 1), Q_new),
                            second = math::CeilQuotient(P_new * (r_new - 1), Q_new);
                    if (first < l) {
                        l_new++;
                    }
                    if (second > r) {
                        r_new--;
                    }
                }
                mid = FMinVal(A_new, B_new, P_new, Q_new,
                               l_new - 1, r_new - 1, RoundingFunction::kCeil);
                mid = mid == 1e18 ? mid : math::CeilQuotient(mid * P_new, Q_new);
                m_val = mid == 1e18 ? mid : static_cast<__int128_t>(B_new) * mid + static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
            }
        }
        break;
        case RoundingFunction::kCellar: {
            if (B_new < 0) {
                {
                    const auto first = math::FloorQuotient(P_new * (l_new + 1), Q_new),
                            second = math::FloorQuotient(P_new * (r_new + 1), Q_new);
                    if (first < l) {
                        l_new++;
                    }
                    if (second > r) {
                        r_new--;
                    }
                }
                mid = FMinVal(A_new, B_new, P_new, Q_new,
                               l_new + 1, r_new + 1, RoundingFunction::kFloor);
                mid = mid == 1e18 ? mid : math::FloorQuotient(mid * P_new, Q_new);
                m_val = mid == 1e18 ? mid : static_cast<__int128_t>(B_new) * mid + static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
            } else {
                {
                    const auto first = math::LoftQuotient(P_new * l_new, Q_new),
                            second = math::LoftQuotient(P_new * r_new, Q_new);
                    if (first < l) {
                        l_new++;
                    }
                    if (second > r) {
                        r_new--;
                    }
                }
                mid = FMinVal(A_new, B_new, P_new, Q_new,
                                                           l_new, r_new, RoundingFunction::kLoft);
                mid = mid == 1e18 ? mid : math::LoftQuotient(mid * P_new, Q_new);
                m_val = mid == 1e18 ? mid : static_cast<__int128_t>(B_new) * mid + static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
            }
        }
    }
    auto min = std::min(l_val, std::min(m_val, r_val));
    if (l_val == min) {
        return l;
    }
    if (m_val == min) {
        return mid;
    }
    return r;
}

long long bin_pow(long long base, long long p, int64_t mod) {
    if (p == 1) {
        return base;
    }

    if (p % 2 == 0) {
        long long t = bin_pow(base, p / 2, mod);
        return t * t % mod;
    } else {
        return bin_pow(base, p - 1, mod) * base % mod;
    }
}

long long inverse_element(int64_t x, int64_t mod) {
    return bin_pow(x, mod - 2, mod);
}

std::pair<int64_t, int64_t> MinAPlusB(int64_t p, int64_t q) {
    assert(q < p);
    if (q == 0) {
        return {0, 1};
    }
    int64_t b = FMinVal(q + 1, -p, q, p, 1, p-1, RoundingFunction::kFloor);
    return {b * q % p, b};
}
