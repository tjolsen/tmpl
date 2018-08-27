//
// Created by tyler on 1/15/18.
//

#ifndef TMPL_VALUE_LIST_FUNCTION_DETAIL_HPP
#define TMPL_VALUE_LIST_FUNCTION_DETAIL_HPP

#include "tmpl_common.hpp"
#include "value_list.hpp"

NAMESPACE_TMPL_DETAIL_OPEN

template <int Start, int End, auto... V, int... I>
auto slice_helper(value_list<V...>, std::integer_sequence<int, I...>) {
    auto f = [](auto &&x, auto c_idx) {
        constexpr auto idx = decltype(c_idx)::value;
        if constexpr ((Start <= idx) && (idx < End)) {
            return x;
        } else {
            return value_list<>{};
        }
    };

    return (f(value_list<V>{}, std::integral_constant<int, I>{}) | ... |
            value_list<>{});
}

NAMESPACE_TMPL_DETAIL_CLOSE

#endif // TMPL_VALUE_LIST_FUNCTION_DETAIL_HPP
