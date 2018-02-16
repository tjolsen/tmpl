//
// Created by tyler on 2/16/18.
//

#include "tmpl.hpp"
#include "catch.hpp"


TEST_CASE("find(type_list)", "[type_list][find]") {
    struct A {};
    struct B {};
    struct C {};
    struct D {};
    auto List = tmpl::type_list<A, B, C, D>{};


    REQUIRE(tmpl::find(List, tmpl::type_list<A>{}) == 0);
    REQUIRE(tmpl::find(List, tmpl::type_list<B>{}) == 1);
    REQUIRE(tmpl::find(List, tmpl::type_list<C>{}) == 2);
    REQUIRE(tmpl::find(List, tmpl::type_list<D>{}) == 3);
}