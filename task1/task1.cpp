#include "task1.h"

int64_t FuncResult(int64_t A, int64_t B, int64_t P, int64_t Q, int64_t l, int64_t r,
                   RoundingFunction g, int64_t prev_l, int64_t prev_r, bool in_l) {
    if (in_l) {
        int64_t val = typeToDivFunc[g](P * l, Q);
        return A * l + B * std::min(std::max(val, prev_l), prev_r);
    } else {
        int64_t val = typeToDivFunc[g](P * r, Q);
        return A * r + B * std::min(std::max(val, prev_l), prev_r);
    }
}

int64_t FMinVal(int64_t A, int64_t B, int64_t P, int64_t Q, int64_t l, int64_t r,
                RoundingFunction g, int64_t prev_l, int64_t prev_r) {
    assert(r >= l);
    if (l == r) {
        return FuncResult(A, B, P, Q, l, r, g, prev_l, prev_r, /* in_l */ true);
    }
    if (B == 0) {
        if (A > 0) {
            return A * l;
        }
        return A * r;
    }
    if (P % Q == 0) {
        int64_t l_result, r_result;
        if (prev_l != std::numeric_limits<int64_t>::min() &&
            prev_r != std::numeric_limits<int64_t>::max()) {
            l_result = FuncResult(A, B, P, Q, l, r, g, prev_l, prev_r, /* in_l */ true);
            r_result = FuncResult(A, B, P, Q, l, r, g, prev_l, prev_r, /* in_l */ false);
        } else {
            l_result = A * l + B * typeToDivFunc[g](P * l, Q);
            r_result = A * r + B * typeToDivFunc[g](P * r, Q);
        }

        return std::min(l_result, r_result);
    }

    const int64_t k = P / Q;
    const int64_t A_new = B, B_new = A + B * k,
                Q_new = P % Q, P_new = Q;
    int64_t l_new = typeToDivFunc[g](Q_new * l, Q), r_new = typeToDivFunc[g](Q_new * r, Q);
    l_new = std::min(std::max(l_new, prev_l), prev_r);
    r_new = std::min(std::max(r_new, prev_l), prev_r);
    switch (g) {
        case RoundingFunction::kFloor: {
            if (B_new < 0) {
                return FMinVal(A_new, B_new, P_new, Q_new,
                               l_new + 1, r_new + 1,RoundingFunction::kCellar, l, r) - A_new;
            } else {
                return FMinVal(A_new, B_new, P_new, Q_new,
                               l_new, r_new, RoundingFunction::kCeil, l,r);
            }
        }
        case RoundingFunction::kCeil: {
            if (B_new < 0) {
                return FMinVal(A_new, B_new, P_new, Q_new,
                               l_new, r_new, RoundingFunction::kFloor,l, r);
            } else {
                return FMinVal(A_new, B_new, P_new, Q_new,
                               l_new - 1, r_new - 1,RoundingFunction::kLoft, l, r) + A_new;
            }
        }
        case RoundingFunction::kLoft: {
            if (B_new < 0) {
                return FMinVal(A_new, B_new, P_new, Q_new,
                               l_new, r_new, RoundingFunction::kCellar,l, r);
            } else {
                return FMinVal(A_new, B_new, P_new, Q_new,
                               l_new - 1, r_new - 1,RoundingFunction::kCeil, l, r) + A_new;
            }
        }
        case RoundingFunction::kCellar: {
            if (B_new < 0) {
                return FMinVal(A_new, B_new, P_new, Q_new,
                               l_new + 1, r_new + 1,RoundingFunction::kFloor, l, r) - A_new;
            } else {
                return FMinVal(A_new, B_new, P_new, Q_new,
                               l_new, r_new, RoundingFunction::kLoft, l,r);
            }
        }
    }
}