//
// Created by tyler on 1/13/18.
//

#include "tmpl.hpp"
#include <iostream>
#include <type_traits>

int main() {

    auto L1 = tmpl::type_list<int, double>{};
    //auto L2 = tmpl::type_list<char, float>{};

    //type_list concatenation
    auto L1L1 = L1 | L1; //can also use tmpl::cat(L1, L1)
    std::cout << std::boolalpha;
    std::cout << "Concatenation successful: "
              << std::is_same_v< decltype(L1L1), tmpl::type_list<int, double, int, double>>
              << std::endl;

    //Reverse a type list
    auto L1_R = tmpl::reverse(L1);
    std::cout << "Reverse successful: "
              << std::is_same_v< decltype(L1_R), tmpl::type_list<double, int>>
              << std::endl;


    //Test if list contains a type
    static_assert(L1.contains(tmpl::type_list<int>{}), "L1 should contain an int");
}