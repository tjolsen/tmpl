//
// Created by tyler on 6/12/18.
//

#ifndef TMPL_TUPLE_UTILS_HPP
#define TMPL_TUPLE_UTILS_HPP

#include "tmpl_common.hpp"
#include "type_list.hpp"
#include "type_list_functions.hpp"
#include "value_list.hpp"
#include "value_list_creation.hpp"
#include <tuple>


NAMESPACE_TMPL_OPEN


namespace detail {
template<typename ...T, typename ...U, int ...Is, int ...Js>
auto tuple_cat_impl(std::tuple<T...> const& L, value_list<Is...>,
                    std::tuple<U...> const& R, value_list<Js...>) {
    return std::make_tuple(std::get<Is>(L)..., std::get<Js>(R)...);
};

}//end namesapce detail

template<typename ...T, typename ...U>
auto tuple_cat(std::tuple<T...> const& L, std::tuple<U...> const& R) {
    constexpr auto Lsize = sizeof...(T);
    constexpr auto Rsize = sizeof...(U);
    return detail::tuple_cat_impl(L, arithmetic_sequence<Lsize>(),
                                  R, arithmetic_sequence<Rsize>());
}

template<typename T, typename ...U>
auto tuple_push_front(std::tuple<U...> const& R, const T& L) {
    return tuple_cat(std::make_tuple(L), R);
};

template<typename T, typename ...U>
auto tuple_push_back(std::tuple<U...> const& L, const T& R) {
    return tuple_cat(L, std::make_tuple(R));
};

template<typename ...T>
constexpr auto tuple_types(std::tuple<T...> const&) {
    return type_list<T...>{};
}


NAMESPACE_TMPL_CLOSE

#endif //TMPL_TUPLE_UTILS_HPP
