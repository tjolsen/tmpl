//
// Created by tyler on 1/14/18.
//

#ifndef TMPL_INT_POW_HPP
#define TMPL_INT_POW_HPP

#include "tmpl_common.hpp"

NAMESPACE_TMPL_OPEN

/**
 *  Compute the power A^B at compile time for integral types
  */
template<typename T, typename U>
constexpr auto int_pow(T A, U B) {

    auto result = T{1};
    for(int i=0; i<B; ++i) {
        result *= A;
    }

    return result;
}

NAMESPACE_TMPL_CLOSE

#endif //TMPL_INT_POW_HPP
