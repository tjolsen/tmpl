//
// Created by tyler on 2/12/18.
//

#ifndef TMPL_SELECT_IF_HPP
#define TMPL_SELECT_IF_HPP

#include "detail/select_if_detail.hpp"
#include "tmpl_common.hpp"
#include "value_list_functions.hpp"

NAMESPACE_TMPL_OPEN

/**
 * Select the elements of a value_list for which a
 * user-supplied unary predicate returns true
 */
template <auto... V, typename F>
constexpr auto select_if(value_list<V...>, F predicate) {

    constexpr auto select_filter = transform(value_list<V...>{}, predicate);

    constexpr auto value_with_filter = zip(value_list<V...>{}, select_filter);

    auto f = [](auto &&x) {
        constexpr auto val_bool = decltype(x){};
        constexpr auto filterBool = val_bool.tail();

        if constexpr (unbox(filterBool)) {
            constexpr auto val = val_bool.head();
            return value_list<unbox(val)>{};
        } else {
            return value_list<>{};
        }
    };

    return detail::select_if_helper(value_with_filter, f);
}

NAMESPACE_TMPL_CLOSE

#endif // TMPL_SELECT_IF_HPP
