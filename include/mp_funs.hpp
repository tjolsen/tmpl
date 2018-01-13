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
auto push_back(type_list<T...>, Type<U>)
{
    return type_list<T..., U>{};
}

template<typename U, typename ...T>
auto push_front(type_list<T...>, Type<U>)
{
    return type_list<U, T...>{};
}

template<typename ...T, typename ...U>
auto cat(type_list<T...>, type_list<U...>)
{
    return type_list<T..., U...>{};
}

template<typename ...T, typename ...U>
auto operator|(type_list<T...> LT, type_list<U...> LU)
{
    return cat(LT, LU);
}

template<typename ...T>
auto reverse(type_list<T...> List)
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
auto make_set(type_list<T...> List)
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
auto set_union(type_list<T...> LT, type_list<U...> LU)
{
    return make_set(LT | LU);
}

/**
 * Return type_list containing elements of LT that are not in LU
 */
template<typename ...T, typename ...U>
auto set_difference(type_list<T...> LT, type_list<U...> LU)
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
auto symmetric_difference(type_list<T...> LT, type_list<U...> LU)
{

    return set_union(set_difference(LT, LU), set_difference(LU, LT));

}

/**
 * Return a default-constructed tuple reflecting what is present
 * in the type_list
 */
template<typename ...T>
auto as_tuple(type_list<T...>)
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


NAMESPACE_TMPL_CLOSE


#endif
