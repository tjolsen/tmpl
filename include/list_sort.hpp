//
// Created by tyler on 1/14/18.
//

#ifndef TMPL_LIST_SORT_HPP
#define TMPL_LIST_SORT_HPP

#include "tmpl_common.hpp"
#include "type_list.hpp"
#include "value_list.hpp"
#include "detail/list_sort_detail.hpp"


NAMESPACE_TMPL_OPEN

/**
 * Implementation of constexpr mergesort on value_list using a user-supplied comparison function
 */
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


/**
 * Implementation of constexpr mergesort on type_list using a user-supplied comparison function
 */
template<typename ...T, typename Compare>
auto sort(type_list<T...> List, Compare && compare) {

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
