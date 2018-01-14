//
// Created by tyler on 1/14/18.
//

#ifndef TMPL_LIST_SORT_DETAIL_HPP
#define TMPL_LIST_SORT_DETAIL_HPP

#include "tmpl_common.hpp"

#include "type_list.hpp"
#include "type_list_functions.hpp"

#include "value_list.hpp"
#include "value_list_functions.hpp"


NAMESPACE_TMPL_DETAIL_OPEN

template<auto ...V, auto ...U, typename Compare>
constexpr auto merge(value_list<V...> A, value_list<U...> B, Compare && compare) {

    if constexpr (A.size() == 0 && B.size() == 0) {
        return value_list<>{};
    }
    else if constexpr (A.size() == 0) {
        return B;
    }
    else if constexpr (B.size() == 0) {
        return A;
    }
    else {

        auto Ahead = A.head();
        auto Bhead = B.head();

        if constexpr (compare(Ahead,Bhead)) {
            return Ahead | merge(A.tail(), B, std::forward<Compare>(compare));
        } else {
            return Bhead | merge(A, B.tail(), std::forward<Compare>(compare));
        }
    }
}


template<typename ...V, typename ...U, typename Compare>
constexpr auto merge(type_list<V...> A, type_list<U...> B, Compare && compare) {

    if constexpr (A.size() == 0 && B.size() == 0) {
        return type_list<>{};
    }
    else if constexpr (A.size() == 0) {
        return B;
    }
    else if constexpr (B.size() == 0) {
        return A;
    }
    else {

        auto Ahead = A.head();
        auto Bhead = B.head();

        if constexpr (compare(Ahead,Bhead)) {
            return Ahead | merge(A.tail(), B, std::forward<Compare>(compare));
        } else {
            return Bhead | merge(A, B.tail(), std::forward<Compare>(compare));
        }
    }
}

NAMESPACE_TMPL_DETAIL_CLOSE

#endif //TMPL_LIST_SORT_DETAIL_HPP
