//
// Created by tyler on 1/14/18.
//

#ifndef TMPL_LIST_SORT_HPP
#define TMPL_LIST_SORT_HPP

#include "tmpl_common.hpp"
#include "type_list.hpp"
#include "type_list_functions.hpp"

#include "value_list.hpp"
#include "value_list_functions.hpp"

NAMESPACE_TMPL_OPEN


namespace detail {

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

} //end namespace detail


template<auto ...V, typename Compare>
auto sort(value_list<V...> List, Compare && compare) {

    if constexpr (List.size() == 0 || List.size() == 1) {
        return List;
    }
    else {

        constexpr auto Midpoint = List.size()/2;
        return detail::merge(slice<0,Midpoint>(List), slice<Midpoint, List.size()>(List), compare);
    }
}


NAMESPACE_TMPL_CLOSE

#endif //TMPL_LIST_SORT_HPP
