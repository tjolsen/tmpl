//
// Created by tyler on 1/13/18.
//

#include "tmpl.hpp"
#include <iostream>

int main() {

    constexpr auto List = tmpl::value_list<1,2,3,4,5>{};

    static_assert(List.contains(tmpl::Value<5>{}), "");

    auto Tlist = tmpl::type_list<int,int,int,int,int>{};

    static_assert(tmpl::make_set(tmpl::get_types(List) | Tlist).size() == 1, "");

    constexpr auto tup = tmpl::as_tuple(List);

    //Print a tuple created from a list
    std::cout << "List from tuple:\n";
    tmpl::for_constexpr<0,List.size()>([&tup](auto I) {
        std::cout << std::get<I>(tup) << ' ';
    });
    std::cout << std::endl << std::endl;

    auto sliced_list = tmpl::slice<1,4>(List);

    //print a sliced value_list
    std::cout << "Sliced list:\n";
    tmpl::for_each(sliced_list, [](auto &&x) {
        std::cout << x << ' ';
    });
    std::cout << std::endl << std::endl;


    auto LL = List | List;
    auto sorted_LL = tmpl::sort(LL, [](auto &&a, auto &&b) {return a < b; });

    std::integral_constant<int, tmpl::unbox(sorted_LL.head())> Iconst;

    std::cout << "Sorted list:\n";
    tmpl::for_each(sorted_LL, [](auto &&x) {
        std::cout << x << ' ';
    });
    std::cout << std::endl << std::endl;


    std::cout << "Evens: \n";
    tmpl::for_each(tmpl::select_if(List, [](auto x){ return x%2 == 0; }),
                   [](auto &&x) {std::cout << x << " ";});
    std::cout << "\n";

    std::cout << "Odds: \n";
    tmpl::for_each(tmpl::select_if(List, [](auto x){ return x%2 != 0; }),
                   [](auto &&x) {std::cout << x << " ";});
}