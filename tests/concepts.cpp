//
// Created by tyler on 1/14/18.
//

#include "tmpl.hpp"
#include "catch.hpp"

struct A {
    int a;
    int afunc();
    static int static_afunc();

    using value_type = int;
};

struct B {
    using type = double;
};


TEST_CASE("tmpl_has_member", "[concepts]") {

    CHECK(tmpl_has_member(A,a));
    CHECK(!tmpl_has_member(A,b));
    CHECK(!tmpl_has_member(B,a));
}

TEST_CASE("tmpl_has_nonstatic_member_function", "[concepts]") {

    CHECK(tmpl_has_nonstatic_member_function(A, afunc));
    CHECK(!tmpl_has_nonstatic_member_function(A, bfunc));
    CHECK(!tmpl_has_nonstatic_member_function(A,static_afunc));
    CHECK(!tmpl_has_nonstatic_member_function(B,afunc));
}

TEST_CASE("tmpl_has_static_member_function", "[concepts]") {
    CHECK(!tmpl_has_static_member_function(A, afunc));
    CHECK(!tmpl_has_static_member_function(A, bfunc));
    CHECK(tmpl_has_static_member_function(A,static_afunc));
    CHECK(!tmpl_has_static_member_function(B,afunc));
}

TEST_CASE("tmpl_has_typedef", "[concepts]") {
    CHECK(tmpl_has_typedef(A, value_type));
    CHECK(!tmpl_has_typedef(A, type));
    CHECK(!tmpl_has_typedef(B, value_type));
    CHECK(tmpl_has_typedef(B, type));
}