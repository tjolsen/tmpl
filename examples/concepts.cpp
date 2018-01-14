//
// Created by tyler on 1/13/18.
//

#include "tmpl.hpp"
#include <iostream>

int main()
{

    struct A
    {
        int a;
        int afunc(int, int) { return 0; }
        static int static_afunc() { return 0; }
        using value_type = int;

        bool operator<(const A& other) {
            return a < other.a;
        }
    };

    struct B
    {
    };

    //Test for member "a"
    constexpr bool A_has_a = tmpl_has_member(A, a);
    constexpr bool B_has_a = tmpl_has_member(B, a);

    //Test for typedef "value_type"
    constexpr bool A_has_vt = tmpl_has_typedef(A, value_type);
    constexpr bool B_has_vt = tmpl_has_typedef(B, value_type);

    std::cout << std::boolalpha; //let's be pretty...

    //Demonstrate that concepts really are constexpr
    std::cout << "A.a exists: " << A_has_a << "\n\tand is constexpr? "
              << (std::is_same_v<std::integral_constant<bool, A_has_a>, std::true_type>
                  ? "Is constexpr" : "Isn't constexpr") << std::endl << std::endl;

    std::cout << "B.a exists: " << B_has_a << "\n\tand is constexpr? "
              << (std::is_same_v<std::integral_constant<bool, B_has_a>, std::false_type>
                  ? "Is constexpr" : "Isn't constexpr") << std::endl << std::endl;

    std::cout << "typename A::value_type exists: " << A_has_vt << "\n\tand is constexpr? "
              << (std::is_same_v<std::integral_constant<bool, A_has_vt>, std::true_type>
                  ? "Is constexpr" : "Isn't constexpr") << std::endl << std::endl;

    std::cout << "typename B::value_type exists: " << B_has_vt << "\n\tand is constexpr? "
              << (std::is_same_v<std::integral_constant<bool, B_has_vt>, std::false_type>
                  ? "Is constexpr" : "Isn't constexpr") << std::endl << std::endl;


    std::cout << "A::afunc is nonstatic member function = " << tmpl_has_nonstatic_member_function(A,afunc) <<std::endl;
    std::cout << "A::afunc is static member function = " << tmpl_has_static_member_function(A,afunc) <<std::endl;
    std::cout << "A::static_afunc is nonstatic member function = " << tmpl_has_nonstatic_member_function(A,static_afunc) <<std::endl;
    std::cout << "A::static_afunc is static member function = " << tmpl_has_static_member_function(A,static_afunc) <<std::endl;
    std::cout << "A::a isfunction = " << tmpl_has_nonstatic_member_function(A,a) <<std::endl;
    std::cout << "A::afunc ismember = " << tmpl_has_member(A,afunc) << std::endl;
    std::cout << "B::afunc exists and is nonstatic member function = " << tmpl_has_nonstatic_member_function(B,afunc) <<std::endl;
    std::cout << "B::afunc exists and is static member function = " << tmpl_has_static_member_function(B,afunc) <<std::endl;


    //========================================================

    //Create your own concepts!

    constexpr auto is_lessThan_comparable = tmpl::is_valid([](auto &&x) -> decltype((void)(x < x)){});

    std::cout << "A supports operator< : " << is_lessThan_comparable(tmpl::type_list<A>{}) << std::endl;
    std::cout << "B supports operator< : " << is_lessThan_comparable(tmpl::type_list<B>{}) << std::endl;
}