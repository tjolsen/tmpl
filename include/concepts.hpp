//
// Created by tyler on 1/13/18.
//

#ifndef TMPL_CONCEPTS_HPP
#define TMPL_CONCEPTS_HPP

#include "tmpl_common.hpp"
#include "mp_funs.hpp"
#include <type_traits>

NAMESPACE_TMPL_OPEN

namespace detail {

template<typename F, typename X, typename = void>
struct is_valid_helper : std::false_type
{
};

template<typename F, typename X>
struct is_valid_helper<F, X, std::void_t<std::result_of_t<F(X)>>> : std::true_type
{
};

} //end namespace detail


/**
 * Test whether a given code fragment is valid. Useful for constructing other concepts.
 *
 * Example usage:
 *
 * \code
 * auto has_member_a = tmpl::is_valid([](auto &&x) -> decltype(void(x.a)) {});
 *
 * struct A { int a; };
 * struct B { int b; };
 *
 * has_member_a(tmpl::type_list<A>{}); //constexpr true
 * has_member_a(tmpl::type_list<B>{}); //constexpr false
 * \endcode
 */
template<typename F>
constexpr auto is_valid(F f)
{
    return [](auto &&x) {
        return detail::is_valid_helper<F, decltype(unbox(x))>::value;
    };
}

NAMESPACE_TMPL_CLOSE

/**
 * Macro definition to test if TYPE has a member called MEMBER
 */
#define tmpl_has_member(TYPE, MEMBER) \
    tmpl::is_valid([](auto &&x) constexpr -> decltype((void)x.MEMBER) {})(tmpl::type_list<TYPE>{})


/**
 * Macro to test whether a type TYPE has a public typedef TYPEDEF_NAME
 */
#define tmpl_has_typedef(TYPE, TYPEDEF_NAME) \
    tmpl::is_valid([](auto &&x) constexpr ->decltype((void)(std::declval<typename std::decay_t<decltype(x)>::value_type>())) \
    {})(tmpl::type_list<TYPE>{})

#endif //TMPL_CONCEPTS_HPP
