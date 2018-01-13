//
// Created by tyler on 1/13/18.
//

#ifndef TMPL_TYPE_COLLECTIONS_HPP
#define TMPL_TYPE_COLLECTIONS_HPP

#include "tmpl_common.hpp"
#include "type_list.hpp"

NAMESPACE_TMPL_OPEN

/**
 * Collection of all (fundamental) integral types.
 * List built from inspection of std::is_integral source
 */
using integral_types = type_list<
        bool,
        char,
        signed char,
        unsigned char,
        char16_t,
        char32_t,
#ifdef _GLIBCXX_USE_WCHAR_T
        wchar_t,
#endif
        short,
        unsigned short,
        int,
        unsigned int,
        long,
        unsigned long,
        long long,
        unsigned long long
>;


/**
 * List of all (fundamental) floating point types.
 * List built from inspection of std::is_integral source
 */
using floating_point_types = type_list<
        float,
        double,
        long double
#if !defined(__STRICT_ANSI__) && defined(_GLIBCXX_USE_FLOAT128)
        , __float128
#endif
>;


NAMESPACE_TMPL_CLOSE

#endif //TMPL_TYPE_COLLECTIONS_HPP
