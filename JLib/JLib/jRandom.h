#pragma once

#include "../extern/rand48/erand48.h"

namespace jLib{
namespace jMath{
namespace jRandom{

inline double jerand48(unsigned short (&xseed)[3])
{
    return erand48(xseed);
}

}}}