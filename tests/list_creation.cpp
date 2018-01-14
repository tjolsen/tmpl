//
// Created by tyler on 1/14/18.
//

#include "catch.hpp"
#include "type_list_creation.hpp"
#include "value_list_creation.hpp"

#include <iostream>

#include <type_traits>

using namespace tmpl;

TEST_CASE("iterate_type", "[type_list]") {

    auto Reference = type_list<int,int,int,int,int> {};
    auto Iterated = iterate_type<int,5>();

    REQUIRE((std::is_same_v<decltype(Reference), decltype(Iterated)>));
}


TEST_CASE("iterate_value", "[value_list]") {

    auto Reference = value_list<1,1,1,1,1>{};
    auto Iterated = iterate_value<1,5>();

    REQUIRE((std::is_same_v<decltype(Reference), decltype(Iterated)>));
}

TEST_CASE("arithmetic_sequence", "[value_list]") {
    auto Ref_0 = value_list<0,1,2,3,4>{};
    auto seq_0 = arithmetic_sequence<Ref_0.size()>();

    auto Reference = value_list<1,2,3,4,5,6>{};
    auto seq = arithmetic_sequence<6,1>();

    REQUIRE((std::is_same_v<decltype(Ref_0), decltype(seq_0)>));
    REQUIRE((std::is_same_v<decltype(Reference), decltype(seq)>));
}

TEST_CASE("geometric_sequence", "[value_list]") {

    auto Ref_2 = value_list<1,2,4,8,16>{};
    auto Ref_3 = value_list<1,3,9,27,81>{};

    auto gseq_2 = geometric_sequence<Ref_2.size(), 2>();
    auto gseq_3 = geometric_sequence<Ref_3.size(), 3>();

    CHECK((std::is_same_v<decltype(Ref_2), decltype(gseq_2)>));
    CHECK((std::is_same_v<decltype(Ref_3), decltype(gseq_3)>));
}