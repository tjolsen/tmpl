//
// Created by tyler on 1/14/18.
//

#ifndef TMPL_VALUE_LIST_MATH_HPP
#define TMPL_VALUE_LIST_MATH_HPP

#include "tmpl_common.hpp"
#include "value_list.hpp"
#include "value_list_functions.hpp"

NAMESPACE_TMPL_OPEN

template<auto ...V>
constexpr auto sum(value_list<V...>) {
    return (V + ...);
}


template<auto ...V>
constexpr auto minimum (value_list<V...> List) {
    auto result = unbox(List.head());

    auto min_func = [&result](auto &&x) {
        using std::min;
        result = min(result, x);
    };

    (min_func(V), ...);

    return result;
}

template<auto ...V>
constexpr auto maximum (value_list<V...> List) {
    auto result = unbox(List.head());

    auto min_func = [&result](auto &&x) {
        using std::max;
        result = max(result, x);
    };

    (min_func(V), ...);

    return result;
}

template<auto ...V, auto ...U>
constexpr auto dot(value_list<V...>, value_list<U...>) {
    return sum(value_list<(V*U)...>{});
}


NAMESPACE_TMPL_CLOSE

#endif //TMPL_VALUE_LIST_MATH_HPP
