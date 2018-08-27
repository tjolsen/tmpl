//
// Created by tyler on 1/14/18.
//

#ifndef TMPL_TYPE_VALUE_PAIR_HPP
#define TMPL_TYPE_VALUE_PAIR_HPP

#include "tmpl_common.hpp"
#include "type_list.hpp"
#include "value_list.hpp"

NAMESPACE_TMPL_OPEN

/**
 * Struct to hold a type and a value (not necessarily related).
 * It is meant to be the element in a type_list resulting from
 * a "zip" operation between a type_list and a value_list.
 */
template <typename T, auto V> struct tv_pair {
    constexpr auto type() { return type_list<T>{}; }
    constexpr auto value() { return V; }
};

template <typename... T, auto... V>
constexpr auto zip(type_list<T...> Tlist, value_list<V...> Vlist) {
    static_assert(Tlist.size() == Vlist.size(), "Lists must have equal length");
    return (type_list<tv_pair<T, V>>{} | ... | type_list<>{});
}

template <typename... T, auto... V>
constexpr auto zip(value_list<V...> Vlist, type_list<T...> Tlist) {
    static_assert(Tlist.size() == Vlist.size(), "Lists must have equal length");
    return (type_list<tv_pair<T, V>>{} | ... | type_list<>{});
}

NAMESPACE_TMPL_CLOSE

#endif // TMPL_TYPE_VALUE_PAIR_HPP
