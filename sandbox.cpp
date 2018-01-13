
#include "tmpl.hpp"
#include <iostream>
#include <string>
#include <typeinfo>

using std::cout;
using std::endl;

template<typename ...T>
void test_contents(tmpl::type_list<T...> List)
{

    auto MasterList = tmpl::integral_types{} | tmpl::floating_point_types{};

    tmpl::for_each(MasterList, [List](auto x) {
        auto val = tmpl::unbox(x);

        cout << typeid(val).name() << ": " << List.contains(x) << endl;
    });
}


int main()
{

    struct A {
        int a;
        using value_type = double;
    };
    struct B {
        int b;
    };

    constexpr bool aa = tmpl_has_member(A,a);
    constexpr bool ba = tmpl_has_member(B,a);
    std::integral_constant<bool, aa> Aacheck;
    std::integral_constant<bool, ba> Bacheck;

    cout << "A has member a: " << tmpl_has_member(A,a) << endl;
    cout << "B has member a: " << tmpl_has_member(B,a) << endl;

    cout << "A has value_type: " << tmpl_has_typedef(A,value_type) << endl;
    cout << "B has value_type: " << tmpl_has_typedef(B,value_type) << endl;

}
