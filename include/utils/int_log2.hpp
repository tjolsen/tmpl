//
// Created by tyler on 4/14/18.
//

#ifndef TMPL_INT_LOG2_HPP
#define TMPL_INT_LOG2_HPP

#include "tmpl_common.hpp"

NAMESPACE_TMPL_OPEN

constexpr int log2(int N) {
    if (N < 0) {
        throw "Cannot pass negative int to log2";
    }
    int result = 0;
    while (N / 2 > 0) {
        ++result;
        N /= 2;
    }
    return result;
};

NAMESPACE_TMPL_CLOSE

#endif // TMPL_INT_LOG2_HPP
