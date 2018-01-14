//
// Created by tyler on 1/13/18.
//

#ifndef TMPL_CONCEPTS_HPP
#define TMPL_CONCEPTS_HPP

#include "tmpl_common.hpp"
#include "type_list.hpp"
#include "type_list_functions.hpp"

#include "value_list.hpp"

#include "detail/concepts_detail.hpp"
#include <type_traits>

NAMESPACE_TMPL_OPEN



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


///@{
/**
 * Trait to test whether a type is a type_list
 */
template<typename ...T>
struct is_type_list : std::false_type {};

template<typename ...T>
struct is_type_list<type_list<T...>> : std::true_type {};

template<typename ...T>
inline bool is_type_list_v = is_type_list<T...>::value;
///@}


///@{
/**
 * Trait to test whether a type is a value_list
 */
template<typename T>
struct is_value_list : std::false_type {};

template<auto ...V>
struct is_value_list<value_list<V...>> : std::true_type {};

template<typename T>
inline bool is_value_list_v = is_value_list<T>::value;
///@}





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
    tmpl::is_valid([](auto &&x) constexpr ->decltype((void)(std::declval<typename std::decay_t<decltype(x)>::TYPEDEF_NAME>())) \
    {})(tmpl::type_list<TYPE>{})

/**
 * Macro to test whether a type TYPE has a public member function MEMBER
 */
#define tmpl_has_nonstatic_member_function(TYPE, MEMBER)             \
    tmpl::is_valid([](auto &&x) constexpr -> std::enable_if_t<       \
            std::is_function_v<                                      \
                 tmpl::detail::member_ptr_helper_t<                  \
                 decltype(&std::decay_t<decltype(x)>::MEMBER)        \
                 >                                                   \
            >                                                        \
    >{})(tmpl::type_list<TYPE>{})

#define tmpl_has_static_member_function(TYPE, MEMBER)                \
    tmpl::is_valid([](auto &&x) constexpr -> std::enable_if_t<       \
            std::is_function_v<                                      \
                 std::remove_pointer_t<                              \
                 decltype(&std::decay_t<decltype(x)>::MEMBER)        \
                 >                                                   \
            >                                                        \
    >{})(tmpl::type_list<TYPE>{})



#endif //TMPL_CONCEPTS_HPP
