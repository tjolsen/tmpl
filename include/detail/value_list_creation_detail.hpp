//
// Created by tyler on 1/14/18.
//

#ifndef TMPL_VALUE_LIST_CREATION_DETAIL_HPP
#define TMPL_VALUE_LIST_CREATION_DETAIL_HPP

#include "tmpl_common.hpp"
#include "value_list.hpp"
#include <type_traits>

NAMESPACE_TMPL_DETAIL_OPEN

template <auto V, auto... VV> constexpr auto add_const(value_list<VV...>) {
    return value_list<V + VV...>{};
};

template <typename T, T... V>
constexpr auto
value_list_from_integer_sequence(std::integer_sequence<T, V...>) {
    return value_list<V...>{};
};

NAMESPACE_TMPL_DETAIL_CLOSE

#endif // TMPL_VALUE_LIST_CREATION_DETAIL_HPP
