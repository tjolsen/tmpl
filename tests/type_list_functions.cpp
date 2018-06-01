//
// Created by tyler on 6/1/18.
//

#include "type_list_functions.hpp"
#include "type_collections.hpp"
#include "catch.hpp"

TEST_CASE("transform(type_list, F)", "[type_list_functions]") {

    auto swapper = [](auto &&x) {
        using T = std::decay_t<decltype(x)>;
        if constexpr(tmpl::floating_point_types{}.contains(T{})) {
            return tmpl::type_list<int>{};
        } else {
            return tmpl::type_list<float>{};
        }
    };


    auto duplicator = [](auto &&x) {
        using T = std::decay_t<decltype(x)>;
        return T{} | T{};
    };

    constexpr auto input = tmpl::type_list<int, double, int, double>{};
    constexpr auto answer = tmpl::type_list<float,int,float,int>{};
    constexpr auto output = tmpl::transform(input, swapper);
    CHECK(output == answer);


    constexpr auto answer2 = tmpl::type_list<int,int, double, double, int, int, double, double>{};
    constexpr auto output2 = tmpl::transform(input, duplicator);
    CHECK(output2 == answer2);
}