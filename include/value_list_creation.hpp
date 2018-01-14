//
// Created by tyler on 1/14/18.
//

#ifndef TMPL_VALUE_LIST_CREATION_HPP
#define TMPL_VALUE_LIST_CREATION_HPP

#include "tmpl_common.hpp"
#include "value_list.hpp"
#include "value_list_functions.hpp"
#include "detail/value_list_creation_detail.hpp"

#include "utils/int_pow.hpp"

NAMESPACE_TMPL_OPEN

/**
 * Make a value_list containing N instances of type T.
 * Attempts to reduce the number of type instantiations
 * that a naive (inheritance-based) implementation would
 * create. This version instantiates O(logN) types rather
 * than O(N) of an inheritance-based version.
 */
template<auto V, int N>
constexpr auto iterate_value() {

    if constexpr (N == 0) {
        return value_list<>{};
    } else if constexpr (N == 1) {
        return value_list<V>{};
    } else {
        constexpr auto Nhalf = N/2;
        return iterate_value<V,Nhalf>() | iterate_value<V, N-Nhalf>();
    }

}


/**
 * Make a value_list containing an arithmetic sequence:
 *
 * decltype(arithmetic_sequence<N,S>()) == value_list<S, S+1, ..., S+N-1>
 *
 * Like iterate_value, it attempts to reduce the number of types instantiated
 * by the compiler.
 *
 * @tparam N Number of terms in sequence
 * @tparam Start Starting value (default = 0)
 */
template<int N, int Start = 0>
auto arithmetic_sequence() {

    static_assert(N >= 0, "Must specify a non-negative sequence length");

    if constexpr(N==0) {
        return value_list<>{};
    }
    else if constexpr (N == 1) {
        return value_list<Start>{};
    } else {

        constexpr auto Nhalf = N/2;
        auto Nhalf_seq_S0 = arithmetic_sequence<Nhalf,0>();

        if constexpr (Nhalf*2 < N) {
            return detail::add_const<Start>(Nhalf_seq_S0) | (detail::add_const<Start+Nhalf>(Nhalf_seq_S0) | value_list<Start + N - 1>{});
        } else {
            return detail::add_const<Start>(Nhalf_seq_S0) | detail::add_const<Start+Nhalf>(Nhalf_seq_S0);
        }
    }
}


/**
 * Create a geometric sequence of length N with base B.
 * The sequence always starts at 1. If you want something else,
 * creating a basic geometric_sequence and further transforming it will
 * be easier.
 */
template<int N, int B>
auto geometric_sequence() {
    auto arith = arithmetic_sequence<N>();

    return transform(arith, [](auto &&x) { return int_pow(B, x); });
}

NAMESPACE_TMPL_CLOSE

#endif //TMPL_VALUE_LIST_CREATION_HPP
