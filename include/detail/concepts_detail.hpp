//
// Created by tyler on 1/14/18.
//

#ifndef TMPL_CONCEPTS_DETAIL_HPP
#define TMPL_CONCEPTS_DETAIL_HPP

#include "tmpl_common.hpp"
#include <type_traits>

NAMESPACE_TMPL_DETAIL_OPEN

template<typename F, typename X, typename = void>
struct is_valid_helper : std::false_type
{
};

template<typename F, typename X>
struct is_valid_helper<F, X, std::void_t<std::result_of_t<F(X)>>> : std::true_type
{
};

template<typename>
struct member_ptr_helper
{
};

template<typename U, typename T>
struct member_ptr_helper<U T::*>
{
    using type = U;
};

template<typename T>
using member_ptr_helper_t = typename member_ptr_helper<T>::type;


NAMESPACE_TMPL_DETAIL_CLOSE

#endif //TMPL_CONCEPTS_DETAIL_HPP
