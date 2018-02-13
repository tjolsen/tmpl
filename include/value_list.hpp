//
// Created by tyler on 1/13/18.
//

#ifndef TMPL_VALUE_LIST_HPP
#define TMPL_VALUE_LIST_HPP

#include "tmpl_common.hpp"

NAMESPACE_TMPL_OPEN

template<auto ...V>
struct value_list
{
private:

    template<auto ...U>
    struct value_list_{};

    template<auto U, auto ...Tail>
    struct value_list_<U, Tail...> {
        constexpr static auto head() { return value_list<U>{}; }
        constexpr static auto tail() { return value_list<Tail...>{}; }
    };


public:
    static constexpr int size() { return sizeof...(V); }

    template<auto U>
    static constexpr bool contains(value_list<U>) {
        auto f = [](auto &&xv, auto &&xu) {
            return std::is_same_v<std::decay_t<decltype(xv)>, std::decay_t<decltype(xu)>>
                && (xv == xu);
        };
        return ( f(V,U) || ...);
    }


    static constexpr auto head()
    {
        return value_list_<V...>::head();
    }

    static constexpr auto tail()
    {
        return value_list_<V...>::tail();
    }

};

/**
 * Type alias for a value list with a single element
 */
template<auto V>
using Value = value_list<V>;

NAMESPACE_TMPL_CLOSE

#endif //TMPL_VALUE_LIST_HPP
