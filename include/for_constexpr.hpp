#ifndef FOR_CONSTEXPR_HPP
#define FOR_CONSTEXPR_HPP

#include "tmpl_common.hpp"
#include <type_traits>
#include <utility>

NAMESPACE_TMPL_OPEN

namespace detail {
template<int ...I, int S, typename F>
constexpr void for_constexpr_impl(std::integer_sequence<int, I...>, std::integral_constant<int, S>, F &&f)
{
    (f(std::integral_constant < int, I + S > {}), ...);
}

}//end namespace detail

/**
 * "Constexpr" for loop that will explicitly unroll
 * a function passed to it. The function "F" will be
 * called with a std::integral_constant<int, I>, where
 * Start <= I < End (i.e., the typical use-case for a for-loop).
 */
template<int Start, int End, typename F>
constexpr void for_constexpr(F &&f)
{

    static_assert(std::is_same_v < void, std::result_of_t < F(std::integral_constant < int, Start > ) >> ,
                  "for_constexpr: Function must return void (for now?)");

    detail::for_constexpr_impl(std::make_integer_sequence < int, End - Start > {},
                               std::integral_constant < int, Start > {},
                               std::forward<F>(f));

}

NAMESPACE_TMPL_CLOSE


#endif
