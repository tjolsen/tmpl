#ifndef TMPL_TYPE_NAME
#define TMPL_TYPE_NAME

#include "tmpl_common.hpp"

NAMESPACE_TMPL_OPEN

template<class T>
constexpr std::string_view type_name() {
    using namespace std;
#ifdef __clang__
    string_view p     = __PRETTY_FUNCTION__;
    string_view key   = "[T = ";
    auto        start = p.find(key);
    return string_view(p.data() + start + key.size(),
                       p.find(']', start) - start - key.size());
    // return string_view(p.data() + 34, p.size() - 34 - 1);
#elif defined(__GNUC__)
    string_view p = __PRETTY_FUNCTION__;
#if __cplusplus < 201402
    return string_view(p.data() + 36, p.size() - 36 - 1);
#else
    string_view key   = "with T = ";
    auto        start = p.find(key);
    return string_view(p.data() + start + key.size(),
                       p.find(';', start) - start - key.size());
#endif
#elif defined(_MSC_VER)
    string_view p = __FUNCSIG__;
    return string_view(p.data() + 84, p.size() - 84 - 7);
#endif
}

NAMESPACE_TMPL_CLOSE

#endif
