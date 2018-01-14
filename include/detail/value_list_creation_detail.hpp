//
// Created by tyler on 1/14/18.
//

#ifndef TMPL_VALUE_LIST_CREATION_DETAIL_HPP
#define TMPL_VALUE_LIST_CREATION_DETAIL_HPP

#include "tmpl_common.hpp"
#include "value_list.hpp"

NAMESPACE_TMPL_DETAIL_OPEN

template<auto V, auto ...VV>
auto add_const(value_list<VV...>) {
    return value_list<V + VV...>{};
};

NAMESPACE_TMPL_DETAIL_CLOSE

#endif //TMPL_VALUE_LIST_CREATION_DETAIL_HPP
