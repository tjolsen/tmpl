//
// Created by tyler on 4/14/18.
//

#include "tmpl.hpp"
#include <utility>

using namespace tmpl;

int main() {

    constexpr auto std_seq = std::make_index_sequence<10>();
    constexpr auto tmpl_seq = geometric_sequence<10,2>();

    return tmpl_seq.size() == std_seq.size();
}