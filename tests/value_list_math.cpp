//
// Created by tyler on 1/14/18.
//

#include "tmpl.hpp"
#include "catch.hpp"

using namespace tmpl;

TEST_CASE("sum(value_list)", "[value_list]") {
    auto list = value_list<1,2,3,4,5>{};
    REQUIRE(sum(list) == 15);
}

TEST_CASE("maximum(value_list)", "[value_list]") {
    auto list = value_list<1,2,3,4,5>{};
    REQUIRE(maximum(list) == 5);
}

TEST_CASE("minimum(value_list)", "[value_list]") {
    auto list = value_list<1,2,3,4,5>{};
    REQUIRE(minimum(list) == 1);
}

TEST_CASE("dot(value_list, value_list)", "[value_list]") {
    auto list = value_list<1,2,3>{};
    auto list2 = value_list<1,2,3>{};
    REQUIRE(dot(list,list2) == 14);
}