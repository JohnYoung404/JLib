#pragma once
#include <type_traits>

#define jConstrain_is_subclass(Derived, Base) typename = jLib::jMPL::enable_if_is_subclass<Derived, Base>

namespace jLib{
namespace jMPL
{
    template<typename Derived, typename Base>
    using enable_if_is_subclass = std::enable_if_t<std::is_base_of<Base, Derived>::value>;     // void if true, error type if false.

}}