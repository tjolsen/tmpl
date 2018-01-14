//
// Created by tyler on 1/14/18.
//

#ifndef TMPL_VALUE_LIST_FUNCTIONS_HPP
#define TMPL_VALUE_LIST_FUNCTIONS_HPP

#include "tmpl_common.hpp"
#include "value_list.hpp"
#include "type_list.hpp"

NAMESPACE_TMPL_OPEN

template<auto ...V, auto U>
constexpr auto push_back(value_list<V...>, value_list<U>) {
    return value_list<V..., U>{};
}

template<auto ...V, auto U>
constexpr auto push_front(value_list<V...>, value_list<U>) {
    return value_list<U, V...>{};
}

template<auto ...V, auto ...U>
constexpr auto cat(value_list<V...>, value_list<U...>) {
    return value_list<V..., U...>{};
}

template<auto ...V, auto ...U>
constexpr auto operator|(value_list<V...> A, value_list<U...> B) {
    return cat(A,B);
}

template<auto ...T>
constexpr auto reverse(value_list<T...> List)
{
    if constexpr (List.size() == 0)
    {
        return List;
    } else {
        return push_back(reverse(List.tail()), List.head());
    }
}

/**
 * pull the value out of a single-item value list
 */
template<auto V>
constexpr auto unbox(value_list<V>) {
    return V;
}

/**
 * Return a type_list of the types of the values in a value_list
 */
template<auto ...V>
constexpr auto get_types(value_list<V...>) {
    return type_list<decltype(V)...>{};
}

/**
 * Return a tuple containing all of the values
 */
template<auto ...V>
constexpr auto as_tuple(value_list<V...>) {
    return std::make_tuple(V...);
}

NAMESPACE_TMPL_CLOSE

#endif //TMPL_VALUE_LIST_FUNCTIONS_HPP
