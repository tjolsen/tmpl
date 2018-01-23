#ifndef TYPE_LIST_HPP
#define TYPE_LIST_HPP

#include "tmpl_common.hpp"
#include <type_traits>

NAMESPACE_TMPL_OPEN

template<typename ...T>
struct type_list
{
    static constexpr int size() { return sizeof...(T); }

    template<typename U>
    static constexpr bool contains(type_list<U>)
    {
        return (std::is_same_v < U, T > || ...);
    }

    template<typename U>
    static constexpr bool contains(U const&)
    {
        return contains(type_list<U>{});
    }


    static constexpr auto head()
    {
        return head_impl(type_list<T...>{});
    }

    static constexpr auto tail()
    {
        return tail_impl(type_list<T...>{});
    }

private:

    template<typename U, typename ...UU>
    static constexpr auto head_impl(type_list<U, UU...>)
    {
        return type_list<U>{};
    }

    template<typename U, typename ...UU>
    static constexpr auto tail_impl(type_list<U, UU...>)
    {
        return type_list<UU...>{};
    }
};

//Compare two type lists
template<typename ...T, typename ...U>
static constexpr bool operator==(type_list<T...>, type_list<U...>) {
    return (std::is_same_v<T,U> && ...);
}


template<typename T>
using Type = type_list<T>;

NAMESPACE_TMPL_CLOSE

#endif
