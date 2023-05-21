#include "task1.h"

const int64_t bad_index = std::numeric_limits<int64_t>::max();

// f(x) = Ax + Bg( Px / Q), x in [l, l + 1, ..., r], Q != 0
int64_t FMinVal(int64_t A, int64_t B, int64_t P, int64_t Q, int64_t l, int64_t r,
                RoundingFunction g) {
    if (l > r) {
        return bad_index;
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
                    const auto first = math::StrongFloorQuotient(P_new * (l_new + 1), Q_new),
                         second = math::StrongFloorQuotient(P_new * (r_new + 1), Q_new);
                    if (first < l) {
                        l_new++;
                    }
                    if (second > r) {
                        r_new--;
                    }
                }
                auto pos = FMinVal(A_new, B_new, P_new, Q_new, // -A_new
                               l_new + 1, r_new + 1, RoundingFunction::kStrongFloor);
                if (pos != bad_index) {
                    mid = math::StrongFloorQuotient(pos * P_new, Q_new);
                    m_val = static_cast<__int128_t>(B_new) * mid + static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
                }
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
                auto pos = FMinVal(A_new, B_new, P_new, Q_new,
                                                           l_new, r_new, RoundingFunction::kCeil);
                if (pos != bad_index) {
                    mid = math::CeilQuotient(pos * P_new, Q_new);
                    m_val = static_cast<__int128_t>(B_new) * mid + static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
                }
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
                auto pos = FMinVal(A_new, B_new, P_new, Q_new,
                                                           l_new, r_new, RoundingFunction::kFloor);
                if (pos != bad_index) {
                    mid = math::FloorQuotient(pos * P_new, Q_new);
                    m_val = static_cast<__int128_t>(B_new) * mid +
                                                static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
                }

            } else {
                {
                    const auto first = math::StrongCeilQuotient(P_new * (l_new - 1), Q_new),
                            second = math::StrongCeilQuotient(P_new * (r_new - 1), Q_new);
                    if (first < l) {
                        l_new++;
                    }
                    if (second > r) {
                        r_new--;
                    }
                }
                auto pos = FMinVal(A_new, B_new, P_new, Q_new,
                               l_new - 1, r_new - 1, RoundingFunction::kStrongCeil);
                if (pos != bad_index) {
                    mid = math::StrongCeilQuotient(pos * P_new, Q_new);
                    m_val = static_cast<__int128_t>(B_new) * mid + static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
                }
            }
        }
        break;
        case RoundingFunction::kStrongCeil: {
            if (B_new < 0) {
                {
                    const auto first = math::StrongFloorQuotient(P_new * l_new, Q_new),
                            second = math::StrongFloorQuotient(P_new * r_new, Q_new);
                    if (first < l) {
                        l_new++;
                    }
                    if (second > r) {
                        r_new--;
                    }
                }
                auto pos = FMinVal(A_new, B_new, P_new, Q_new,
                                                           l_new, r_new, RoundingFunction::kStrongFloor);
                if (pos != bad_index) {
                    mid = math::StrongFloorQuotient(pos * P_new, Q_new);
                    m_val = static_cast<__int128_t>(B_new) * mid + static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
                }
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
                auto pos = FMinVal(A_new, B_new, P_new, Q_new,
                               l_new - 1, r_new - 1, RoundingFunction::kCeil);
                if (pos != bad_index) {
                    mid = math::CeilQuotient(pos * P_new, Q_new);
                    m_val = static_cast<__int128_t>(B_new) * mid + static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
                }
            }
        }
        break;
        case RoundingFunction::kStrongFloor: {
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
                auto pos = FMinVal(A_new, B_new, P_new, Q_new,
                               l_new + 1, r_new + 1, RoundingFunction::kFloor);
                if (pos != bad_index) {
                    mid = math::FloorQuotient(pos * P_new, Q_new);
                    m_val = static_cast<__int128_t>(B_new) * mid + static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
                }
            } else {
                {
                    const auto first = math::StrongCeilQuotient(P_new * l_new, Q_new),
                            second = math::StrongCeilQuotient(P_new * r_new, Q_new);
                    if (first < l) {
                        l_new++;
                    }
                    if (second > r) {
                        r_new--;
                    }
                }
                auto pos = FMinVal(A_new, B_new, P_new, Q_new,
                                                           l_new, r_new, RoundingFunction::kStrongCeil);
                if (pos != bad_index) {
                    mid = math::StrongCeilQuotient(pos * P_new, Q_new);
                    m_val = static_cast<__int128_t>(B_new) * mid + static_cast<__int128_t>(B) * typeToDivFunc[g](Q_new * mid, Q);
                }
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

std::pair<int64_t, int64_t> MinAPlusB(int64_t p, int64_t q) {
    assert(q < p);
    if (q == 0) {
        return {0, 1};
    }
    int64_t b = FMinVal(q + 1, -p, q, p, 1, p-1, RoundingFunction::kFloor);
    return {b * q % p, b};
}
