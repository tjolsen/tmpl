
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


template<auto First, auto Second>
struct value_pair{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
};


template<auto ...A, auto ...B>
auto operator|(tmpl::value_list<A...>, tmpl::value_list<B...>)
{
        return tmpl::value_list<A..., B...>{};
};

int main()
{
    tmpl::value_list<1,2,3,4> L1;
    tmpl::value_list<1,2,3,4lu> L2;

    tmpl::type_list<int, int, int> T1;
    tmpl::type_list<char, char, char> T2;

    auto Tzip = tmpl::zip(T1,T2);
    tmpl::for_each(Tzip, [](auto &&x) {
        auto xval = tmpl::unbox(x);
        auto a = xval.head();
        auto b = xval.tail();

        auto aval = tmpl::unbox(a);
        auto bval = tmpl::unbox(b);
        aval = 'a';
        bval = 'b';

        cout << "aval = " << aval << "  bval = " << bval << endl;
    });

    auto zipped = zip(L1, L2);

    tmpl::for_each(zipped,
    [](auto &&xT){
        auto x = tmpl::unbox(xT);
        cout << "(" << tmpl::unbox(x.head()) << ", " << tmpl::unbox(x.tail()) << ")" << endl;
    });

}
