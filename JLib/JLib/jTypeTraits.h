#pragma once
#include <type_traits>
#include <boost/type_traits.hpp>
#include "jUtility.h"

#define jConstrain_typename_is_subclass(Derived, Base) typename = jLib::jMPL::enable_if_is_subclass<Derived, Base>
#define jConstrain_typename_num_equal(src, goal) typename = std::enable_if_t<src == goal>
#define jConstrain_typename_floating_point(Type) typename = std::enable_if_t<std::is_floating_point<Type>::value>
#define jConstrain_sentence_is_arithmetic(Type) std::enable_if_t<std::is_arithmetic<Type>::value, int>()

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jMPL)

template<typename Derived, typename Base>
using enable_if_is_subclass = std::enable_if_t<std::is_base_of<Base, Derived>::value>;     // void if true, error type if false.

NAME_SPACE_END
NAME_SPACE_END