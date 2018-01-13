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
        using value_type = int;
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


}