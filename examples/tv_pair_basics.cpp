//
// Created by tyler on 1/14/18.
//

#include "tmpl.hpp"
#include <typeinfo>
#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream& out, tmpl::type_list<T>) {
    out << typeid(T).name();
    return out;
}


int main() {

    auto Tlist = tmpl::type_list<int, double, char, float>{};
    auto Vlist = tmpl::value_list<1,3,2,4>{};

    auto TVlist = tmpl::zip(Tlist, Vlist);

    auto TVlist_sorted = tmpl::sort(TVlist, [](auto &&a, auto &&b){
        return tmpl::unbox(a).value() < tmpl::unbox(b).value();
    });

    auto print_TV = [](auto &&tv) {
        std::cout << "(" << tmpl::unbox(tv).type() << ", " << tmpl::unbox(tv).value() << ")\n";
    };
    tmpl::for_each(TVlist, print_TV);
    std::cout << std::endl << std::endl;
    tmpl::for_each(TVlist_sorted, print_TV);
}