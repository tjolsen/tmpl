#ifndef TMPL_VALUE_LIST_IO_HPP
#define TMPL_VALUE_LIST_IO_HPP

#include "tmpl_common.hpp"
#include "value_list.hpp"
#include <iostream>


NAMESPACE_TMPL_OPEN

template<auto ...V>
std::ostream& operator<<(std::ostream& out, value_list<V...> vl) {
    constexpr auto n = vl.size();

    auto p = [&out](auto &&v) {
		 out << v << ", ";
	     };
    
    out << "tmpl::value_list<";
    (p(V), ...);
    out << ">";
    return out;
}

NAMESPACE_TMPL_CLOSE

#endif
