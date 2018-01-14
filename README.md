TMPL
====

TMPL is a C++17 metaprogramming library that will eventually
replace the metaprogramming facilities in my other projects.
This is mostly done so that I have only a single codebase
to test and maintain, especially since this tends to be a
bug-prone part of code.

Compatibility
-------------
This library requires C++17 features (fold expressions, constexpr if,
constexpr lambdas, auto templates), so a recent compiler is required.
The library is being developed using gcc-7.1 and clang-5.0, so 
it should always work with at least these compilers.

Currently, GCC 7.1 seems to struggle with the constexpr-ness of the
"concepts" (see below/examples). Due to this, it is necessary to
break usage out into two parts:
```C++
constexpr bool Foo_has_bar = tmpl_has_member(Foo, bar); //assume that type "Foo" has a member "bar"
std::integral_constant<bool, Foo_has_bar> Baz;

//This fails to compile with my GCC, works fine with Clang 5.0:
std::integral_constant<bool, tmpl_has_member(Foo,bar)> BadBaz;
```

Installation
------------
The library is header-only, so it can be trivially "built"
and installed using CMake. The commands below will install
it into the default CMake installation location.
```bash
mkdir build
cd build
cmake ..
make install
```

Usage
-----
The easiest way to use tmpl is via CMake, and it can
be included in your project via
```CMake
find_package(tmpl)
target_link_libraries(YourExecutableOrLibrary PUBLIC tmpl::tmpl)
```
Simply include "tmpl.hpp", and all functionality will 
be available. All user-facing types and functions are 
contained in the "tmpl" namespace. An overview of 
functionality is given below.


Basic Types and Operations
--------------------------
The bread-and-butter of the library (so far) is the "type_list".
It is exactly what it sounds like: a list of types inside a template.

```C++
template<typename ...T>
struct type_list {};
```

The type_list can be manipulated as a value to perform
useful operations on the list:
```C++
type_list<int, double, char, myClass> List;

//Get head/tail of list
auto h = List.head(); // decltype(h) == type_list<int>
auto t = List.tail(); //decltype(t) == type_list<double, char, myClass>

// Concatenation
auto L2 = t | h; //decltype(L2) == type_list<double, char, myClass, int>

// Reversal
auto LR = reverse(List); //decltype(LR) == type_list<myClass, char, double, int>

//---------------------------------------------------
// Set operations
//---------------------------------------------------
type_list<int, double, int, double, int, double> ID_Repeated;
type_list<char, int, char, int, char, int> CI_Repeated;

auto ID_Set = make_set(ID_Repeated); //decltype(ID_Set) == type_list<int,double>
auto CI_Set = make_set(CI_Repeated); //decltype(CI_Set) == type_list<char,int>

auto ID_minus_CI = set_difference(ID_Set, CI_Set); // decltype(ID_minus_CI) == type_list<double>
auto CI_minus_ID = set_difference(CI_Set, ID_Set); // decltype(CI_minus_ID) == type_list<char>
auto sym_diff = symmetric_difference(ID_Set, CI_Set); //decltype(sym_diff) == type_list<double, char>
```

There is an alias for a type list with a single type, called
```Type```, which can be "unboxed" to yield a default-constructed
value of the contained type.
```C++
Type<int> T;
auto Tval = unbox(T); //decltype(Tval) == int
```

Concepts
--------
There are also facilities for creating powerful concepts to enforce
constraints on generic code. Inspired by boost::hana, I have included
an "is_valid" function to test whether a code section is valid.
Using this, other concepts can be built for more special-purpose constraints.

Since they are among the most common concepts, I have included macros
that test for the presence of (public) class members and typedefs.

```C++
struct A {
    int a;
    using value_type = int;
};

struct B{};

// use macros to test for members and typedefs:
tmpl_has_member(A, a)

```
