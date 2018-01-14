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

    tmpl::for_constexpr<0,List.size()>([&tup](auto I) {
        std::cout << std::get<I>(tup) << std::endl;
    });
}