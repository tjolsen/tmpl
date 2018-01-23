//
// Created by tyler on 1/15/18.
//

#include "catch.hpp"
#include "value_list_functions.hpp"
#include "concepts.hpp"

using namespace tmpl;

TEST_CASE("push_back(value_list)", "[value_list]")
{
    auto L = value_list<1, 2, 3>{};
    auto x = value_list<4>{};
    auto Ref = value_list<1, 2, 3, 4>{};

    auto test = push_back(L, x);
    REQUIRE((std::is_same_v<decltype(Ref), decltype(test)>));
}

TEST_CASE("push_front(value_list)", "[value_list]")
{
    auto L = value_list<1, 2, 3>{};
    auto x = value_list<4>{};
    auto Ref = value_list<4, 1, 2, 3>{};

    auto test = push_front(L, x);
    REQUIRE((std::is_same_v<decltype(Ref), decltype(test)>));
}

TEST_CASE("cat(value_list, value_list)", "[value_list]")
{
    auto L = value_list<1, 2, 3>{};
    auto R = value_list<4, 5, 6>{};
    auto Ref = value_list<1, 2, 3, 4, 5, 6>{};
    auto test = cat(L, R);
    auto test2 = L | R;
    REQUIRE((std::is_same_v<decltype(Ref), decltype(test)>));
    REQUIRE((std::is_same_v<decltype(Ref), decltype(test2)>));
}

TEST_CASE("reverse(value_list)", "[value_list]")
{
    auto list = value_list<1, 2, 3, 4>{};
    auto Ref = value_list<4, 3, 2, 1>{};
    auto test = reverse(list);
    REQUIRE((std::is_same_v<decltype(Ref), decltype(test)>));
}

TEST_CASE("unbox(value_list)", "[value_list][concepts]")
{
    auto list1 = value_list<1>{};
    auto list12 = value_list<1, 2>{};

    // returns a function that takes a type_list of a single type
    // and checks whether unbox() is a valid function call
    // for the type contained within.
    auto valid_unbox = is_valid([](auto &&x) -> decltype((void) (unbox(x))) {});

    REQUIRE(unbox(list1) == 1);
    REQUIRE((!valid_unbox(type_list<decltype(list12)>{})));
}

TEST_CASE("get_types(value_list)", "[value_list][type_list]")
{
    auto vlist = value_list<1, 2, 'a', 4u>{};
    auto tlist = type_list<int, int, char, unsigned>{};

    REQUIRE((std::is_same_v<decltype(get_types(vlist)), decltype(tlist)>));
}

TEST_CASE("make_set(value_lsit)", "[value_list]")
{
    auto list = value_list<1,2,1,2,1,2>{};
    auto Ref = value_list<1,2>{};
    auto test = make_set(list);
    REQUIRE((std::is_same_v<decltype(Ref), decltype(test)>));
}

TEST_CASE("set_union(value_list, value_list)", "[value_list]")
{
    auto L = value_list<1,2>{};
    auto R = value_list<2,3>{};
    auto Ref = value_list<1,2,3>{};
    auto test = set_union(L,R);
    REQUIRE((std::is_same_v<decltype(Ref), decltype(test)>));

    auto test2 = set_union(R,L);
    auto Ref2 = value_list<3,1,2>{}; //right-to-left nature of make_set inside of set_union
    REQUIRE((std::is_same_v<decltype(Ref2), decltype(test2)>));
}