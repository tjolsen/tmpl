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
    static constexpr int size() { return sizeof...(V); }

    template<auto U>
    static constexpr bool contains(value_list<U>) {
        auto f = [](auto &&xv, auto &&xu) {
            return std::is_same_v<std::decay_t<decltype(xv)>, std::decay_t<decltype(xu)>>
                && (xv == xu);
        };
        return ( f(V,U) || ...);
    }
};

NAMESPACE_TMPL_CLOSE

#endif //TMPL_VALUE_LIST_HPP
