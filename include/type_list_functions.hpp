#ifndef MP_FUNCS_HPP
#define MP_FUNCS_HPP

#include "type_list.hpp"
#include <tuple>

NAMESPACE_TMPL_OPEN

///@{
/**
 * Basic type_list building/manipulation functions
 */
template<typename U, typename ...T>
constexpr auto push_back(type_list<T...>, Type<U>)
{
    return type_list<T..., U>{};
}

template<typename U, typename ...T>
constexpr auto push_front(type_list<T...>, Type<U>)
{
    return type_list<U, T...>{};
}

template<typename ...T, typename ...U>
constexpr auto cat(type_list<T...>, type_list<U...>)
{
    return type_list<T..., U...>{};
}

template<typename ...T, typename ...U>
constexpr auto operator|(type_list<T...> LT, type_list<U...> LU)
{
    return cat(LT, LU);
}

template<typename ...T>
constexpr auto reverse(type_list<T...> List)
{
    if constexpr (List.size() == 0)
    {
        return List;
    } else {
        return push_back(reverse(List.tail()), List.head());
    }
}
///@}

/**
 * Unbox a single-item type_list and return a
 * constexpr default-constructed value of the contained type.
 */
template<typename T>
constexpr T unbox(tmpl::type_list<T>)
{
    return T{};
}


/**
 * Return a type_list containing the unique elements
 */
template<typename ...T>
constexpr auto make_set(type_list<T...> List)
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
template<typename ...T, typename ...U>
constexpr auto set_union(type_list<T...> LT, type_list<U...> LU)
{
    return make_set(LT | LU);
}

/**
 * Return type_list containing elements of LT that are not in LU
 */
template<typename ...T, typename ...U>
constexpr auto set_difference(type_list<T...> LT, type_list<U...> LU)
{

    auto F = [](auto X) {

        //(LU.contains(decltype(X){})) {
        if constexpr (type_list<U...>::contains(decltype(X){}))
        {
            return type_list<>{};
        } else {
            return X;
        }
    };

    return (type_list<>{} | ... | F(type_list<T>{}));
}

/**
 * Symmetric set difference of two sets (type_lists)
 */
template<typename ...T, typename ...U>
constexpr auto symmetric_difference(type_list<T...> LT, type_list<U...> LU)
{

    return set_union(set_difference(LT, LU), set_difference(LU, LT));

}

/**
 * Return a default-constructed tuple reflecting what is present
 * in the type_list
 */
template<typename ...T>
constexpr auto as_tuple(type_list<T...>)
{
    return std::tuple < T...>{};
}

/**
 * Basic for_each loop over elements of the type list
 */
template<typename ...T, typename F>
constexpr void for_each(type_list<T...>, F &&f)
{
    (f(type_list<T>{}), ...);
}

template<typename ...T, typename ...V>
constexpr auto zip(type_list<T...>, type_list<V...>) {
    return (type_list<type_list<T,V>>{} | ... | type_list<>{});
}


namespace detail {

template<int Start, int End, typename ...V, int ...I>
auto slice_helper(type_list<V...>, std::integer_sequence<int, I...>)
{
    auto f = [](auto &&x, auto &&idx) {
        if constexpr ((Start <= idx) && (idx < End))
        {
            return x;
        }
        else {
        return type_list<>{};
    }
    };

    return (f(type_list<V>{}, std::integral_constant<int,I>{}) | ... | type_list<>{});
}

}//end namespace detail

/**
 * Return a slice from a type_list. Returns
 * a list of the elements between Start <= I < End.
 */
template<int Start, int End, typename ...V>
auto slice(type_list<V...> List)
{
    static_assert((Start >=0) && (Start <= End) && End<=List.size(), "tmpl::slice(type_list): Invalid Bounds");
    return detail::slice_helper<Start,End>(List, std::make_integer_sequence<int, List.size()>{});

}


/**
 * Select the elements of a value_list for which a
 * user-supplied unary predicate returns true
 */
template<typename ...T, typename F>
constexpr auto select_if(type_list<T...>, F predicate) {

    constexpr auto f = [predicate](auto x) {
        if constexpr ((bool)predicate(std::decay_t<decltype(x)>{})) {
            return x;
        }
        else {
            return type_list<>{};
        }
    };

    return (f(type_list<T>{}) | ... | type_list<>{});
}


/**
 * Return the index of a type within a type list.
 * Return the length of the type list if the type is not contained.
 */
template<typename ...T, typename V>
constexpr auto find(type_list<T...> List, type_list<V> query) {
    if constexpr (List.size() > 1) {
        return (List.head() == query) ? 0 : 1+find(List.tail(), query);
    } else {
        return List == query ? 0 : 1;
    }

}

NAMESPACE_TMPL_CLOSE


#endif
