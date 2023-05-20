#include "task1.h"

// f(x) = Ax + Bg( Px / Q), x in [l, l + 1, ..., r], Q != 0
__int128_t FMinVal(__int128_t A, __int128_t B, __int128_t P, __int128_t Q, __int128_t l, __int128_t r,
                RoundingFunction g) {
    if (l > r) {
        return 1e30;
    }

    if (l == r) {
        return A * l + B * typeToDivFunc[g](P * l, Q);
    }
    if (B == 0) {
        if (A > 0) {
            return A * l;
        }
        return A * r;
    }
    if (P % Q == 0) {
        const __int128_t l_result = A * l + B * typeToDivFunc[g](P * l, Q),
                      r_result = A * r + B * typeToDivFunc[g](P * r, Q);
        return std::min(l_result, r_result);
    }

    const int64_t k = P / Q;

    const __int128_t A_new = B, B_new = A + B * k,
                Q_new = P % Q, P_new = Q;
    __int128_t l_new = typeToDivFunc[g](Q_new * l, Q), r_new = typeToDivFunc[g](Q_new * r, Q);

    const __int128_t first_candidate = B_new * l + B * l_new, second_candidate = B_new * r + B * r_new;
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
                const __int128_t third_candidate = FMinVal(A_new, B_new, P_new, Q_new,
                               l_new + 1, r_new + 1,RoundingFunction::kCellar) - A_new;
                return std::min(first_candidate, std::min(second_candidate, third_candidate));
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
                const __int128_t third_candidate = FMinVal(A_new, B_new, P_new, Q_new,
                               l_new, r_new, RoundingFunction::kCeil);
                return std::min(first_candidate, std::min(second_candidate, third_candidate));
            }
        }
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
                const __int128_t third_candidate = FMinVal(A_new, B_new, P_new, Q_new,
                               l_new, r_new, RoundingFunction::kFloor);
                return std::min(first_candidate, std::min(second_candidate, third_candidate));
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
                const __int128_t third_candidate = FMinVal(A_new, B_new, P_new, Q_new,
                               l_new - 1, r_new - 1,RoundingFunction::kLoft) + A_new;
                return std::min(first_candidate, std::min(second_candidate, third_candidate));
            }
        }
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
                const __int128_t third_candidate = FMinVal(A_new, B_new, P_new, Q_new,
                               l_new, r_new, RoundingFunction::kCellar);
                return std::min(first_candidate, std::min(second_candidate, third_candidate));
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
                const __int128_t third_candidate = FMinVal(A_new, B_new, P_new, Q_new,
                               l_new - 1, r_new - 1,RoundingFunction::kCeil) + A_new;
                return std::min(first_candidate, std::min(second_candidate, third_candidate));
            }
        }
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
                const __int128_t third_candidate = FMinVal(A_new, B_new, P_new, Q_new,
                               l_new + 1, r_new + 1,RoundingFunction::kFloor) - A_new;
                return std::min(first_candidate, std::min(second_candidate, third_candidate));
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
                const __int128_t third_candidate = FMinVal(A_new, B_new, P_new, Q_new,
                               l_new, r_new, RoundingFunction::kLoft);
                return std::min(first_candidate, std::min(second_candidate, third_candidate));
            }
        }
    }
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
    int64_t a_plus_b = FMinVal(q + 1, -p, q, p, 1, p-1, RoundingFunction::kFloor);
    int64_t b = a_plus_b * inverse_element(q + 1, p) % p;
    int64_t a = a_plus_b - b;
    return {a, b};
}
