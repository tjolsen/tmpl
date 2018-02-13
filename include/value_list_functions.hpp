//
// Created by tyler on 1/14/18.
//

#ifndef TMPL_VALUE_LIST_FUNCTIONS_HPP
#define TMPL_VALUE_LIST_FUNCTIONS_HPP

#include "tmpl_common.hpp"
#include "value_list.hpp"
#include "type_list.hpp"
#include "detail/value_list_function_detail.hpp"

#include <utility>
#include <tuple>

NAMESPACE_TMPL_OPEN

template<auto ...V, auto U>
constexpr auto push_back(value_list<V...>, value_list <U>)
{
    return value_list < V..., U > {};
}

template<auto ...V, auto U>
constexpr auto push_front(value_list<V...>, value_list <U>)
{
    return value_list < U, V...>{};
}

template<auto ...V, auto ...U>
constexpr auto cat(value_list<V...>, value_list<U...>)
{
    return value_list < V..., U...>{};
}

template<auto ...V, auto ...U>
constexpr auto operator|(value_list<V...> A, value_list<U...> B)
{
    return cat(A, B);
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
constexpr auto unbox(value_list <V>)
{
    return V;
}

/**
 * Return a type_list of the types of the values in a value_list
 */
template<auto ...V>
constexpr auto get_types(value_list<V...>)
{
    return type_list < decltype(V)...>{};
}

/**
 * Return a tuple containing all of the values
 */
template<auto ...V>
constexpr auto as_tuple(value_list<V...>)
{
    return std::make_tuple(V...);
}


/**
 * Return a type_list containing the unique elements
 */
template<auto ...T>
constexpr auto make_set(value_list<T...> List)
{
    if constexpr (List.size() == 0)
    {
        return List;
    }
    else {
        auto tail_set = make_set(List.tail());

        if constexpr (!tail_set.contains(List.head()))
        {
            return push_front(tail_set, List.head());
        } else {
            return tail_set;
        }
    }
}


/**
 * Return the set-union of two type lists
 * (this will also remove duplicates from the originals)
 */
template<auto ...T, auto ...U>
constexpr auto set_union(value_list<T...> LT, value_list<U...> LU)
{
    return make_set(LT | LU);
}

/**
 * Return type_list containing elements of LT that are not in LU
 */
template<auto ...T, auto ...U>
constexpr auto set_difference(value_list<T...> LT, value_list<U...> LU)
{

    auto F = [](auto X) {

        //(LU.contains(decltype(X){})) {
        if constexpr (value_list<U...>::contains(decltype(X){}))
        {
            return value_list<>{};
        } else {
        return X;
    }
    };

    return (value_list<>{} | ... | F(value_list < T > {}));
}

/**
 * Symmetric set difference of two sets (type_lists)
 */
template<auto ...T, auto ...U>
constexpr auto symmetric_difference(value_list<T...> LT, value_list<U...> LU)
{

    return set_union(set_difference(LT, LU), set_difference(LU, LT));

}


/**
 * Basic for-each over elements of a value list
 */
template<auto ...V, typename F>
void for_each(value_list<V...>, F &&f)
{
    (f(V), ...);
}


/**
 * Zip two value lists into a type_list of value_lists
 */
template<auto ...V, auto ...U>
constexpr auto zip(value_list<V...>, value_list<U...>)
{
    return (type_list < value_list < V, U >> {} | ... | type_list<>{});
}


/**
 * Return a slice from a value_list. Returns
 * a list of the elements between Start <= I < End.
 */
template<int Start, int End, auto ...V>
auto slice(value_list<V...> List)
{
    static_assert((Start >=0) && (Start <= End) && End<=List.size(), "tmpl::slice(value_list): Invalid Bounds");
    return detail::slice_helper<Start,End>(List, std::make_integer_sequence<int, List.size()>{});
}


/**
 * Apply a function to each value in the value_list
 * and return a new value_list containing these values.
 * Similar to std::transform.
 */
template<auto ...V, typename F>
constexpr auto transform(value_list<V...>, F f) {
    return (value_list<f(V)>{} | ... | value_list<>{});
}


///@{
/**
 * Comparison operators for single-element value lists (aka Values)
 */

template<auto U, auto V>
constexpr bool operator<(Value<U>, Value<V>) {
    return U < V;
}

template<auto U, auto V>
constexpr bool operator<=(Value<U>, Value<V>) {
    return U <= V;
}

template<auto U, auto V>
constexpr bool operator>(Value<U>, Value<V>) {
    return U > V;
}

template<auto U, auto V>
constexpr bool operator>=(Value<U>, Value<V>) {
    return U >= V;
}

template<auto U, auto V>
constexpr bool operator==(Value<U>, Value<V>) {
    return U == V;
}

template<auto U, auto V>
constexpr bool operator!=(Value<U>, Value<V>) {
    return U != V;
}
///@}

NAMESPACE_TMPL_CLOSE

#endif //TMPL_VALUE_LIST_FUNCTIONS_HPP
