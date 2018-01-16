#pragma once
#include "jTypeTraits.h"
#include "jVector.h"

namespace jLib
{
    namespace jMPL
    {
        namespace jVecTraits
        {
            template<typename Type>
            struct is_vec
            {
                static const bool value = __jVecTraits_impl::__is_vec_impl<boost::remove_cv_ref_t<Type>>::value;
            };

            namespace __jVecTraits_impl
            {
                template<typename Type>
                struct __is_vec_impl {
                    static const bool value = false;
                };

                template<typename Type, size_t Degree>
                struct __is_vec_impl<jContainer::jVecBase<Type, Degree>> {
                    static const bool value = true;
                };
            }
        }
    }
}