//
// Created by tyler on 1/14/18.
//

#ifndef TMPL_TYPE_LIST_CREATION_HPP
#define TMPL_TYPE_LIST_CREATION_HPP

#include "tmpl_common.hpp"
#include "type_list.hpp"
#include "type_list_functions.hpp"

NAMESPACE_TMPL_OPEN

/**
 * Make a type_list containing N instances of type T.
 * Attempts to reduce the number of type instantiations
 * that a naive (inheritance-based) implementation would
 * create. This version instantiates O(logN) types rather
 * than O(N) of an inheritance-based version.
 */
template <typename T, int N> constexpr auto iterate_type() {

    if constexpr (N == 0) {
        return type_list<>{};
    } else if constexpr (N == 1) {
        return type_list<T>{};
    } else {
        constexpr auto Nhalf = N / 2;
        if constexpr (Nhalf * 2 < N) {
            return iterate_type<T, Nhalf>() | iterate_type<T, Nhalf>() |
                   type_list<T>{};
        } else {
            return iterate_type<T, Nhalf>() | iterate_type<T, Nhalf>();
        }
    }
};

NAMESPACE_TMPL_CLOSE

#endif // TMPL_TYPE_LIST_CREATION_HPP
