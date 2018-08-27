//
// Created by tyler on 1/19/18.
//

#ifndef TMPL_NULL_HPP
#define TMPL_NULL_HPP

#include "tmpl_common.hpp"
#include <type_traits>

NAMESPACE_TMPL_OPEN

/**
 * \brief An empty struct with a constexpr constructor
 * that can accept any type
 */
struct Null {
    template <typename T> constexpr Null(T &&) {}

    template <typename T,
              typename = typename std::enable_if_t<!std::is_same_v<void, T>>>
    constexpr operator Null(T &&t) {
        return Null(t);
    }

    constexpr operator Null(void) { return Null(int{}); }
};

NAMESPACE_TMPL_CLOSE

#endif // TMPL_NULL_HPP
