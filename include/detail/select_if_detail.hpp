//
// Created by tyler on 2/12/18.
//

#ifndef TMPL_SELECT_IF_DETAIL_HPP
#define TMPL_SELECT_IF_DETAIL_HPP

#include "tmpl_common.hpp"
#include "type_list.hpp"
#include "value_list.hpp"

NAMESPACE_TMPL_DETAIL_OPEN

template<typename ...T, typename F>
constexpr auto select_if_helper(type_list<T...>, F && f) {
    return (f(T{}) | ... | value_list<>{});
}

NAMESPACE_TMPL_DETAIL_CLOSE

#endif //TMPL_SELECT_IF_DETAIL_HPP
