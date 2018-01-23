
#include "tmpl.hpp"
#include <iostream>
#include <string>
#include <typeinfo>

using std::cout;
using std::endl;

using namespace tmpl;

int main()
{

    struct A{};
    struct B{};
    struct C{};
    struct D{};

    auto tl = type_list<A,B,C>{};

    cout << find(tl, Type<A>{}) << endl;
    cout << find(tl, Type<B>{}) << endl;
    cout << find(tl, Type<C>{}) << endl;
    cout << find(tl, Type<D>{}) << endl;
}
