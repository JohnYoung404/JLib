#pragma once
#include <type_traits>
#include <boost/type_traits.hpp>

#define jConstrain_typename_is_subclass(Derived, Base) typename = jLib::jMPL::enable_if_is_subclass<Derived, Base>
#define jConstrain_typename_num_equal(src, goal) typename = std::enable_if_t<src == goal>
#define jConstrain_typename_floating_point(Type) typename = std::enable_if_t<std::is_floating_point<Type>::value>
#define jConstrain_sentence_is_arithmetic(Type) std::enable_if_t<std::is_arithmetic<Type>::value, int>()

namespace jLib{
namespace jMPL
{
    template<typename Derived, typename Base>
    using enable_if_is_subclass = std::enable_if_t<std::is_base_of<Base, Derived>::value>;     // void if true, error type if false.

}}