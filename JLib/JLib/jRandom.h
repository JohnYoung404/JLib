#pragma once

#include <mutex>
#include "../extern/rand48/erand48.h"
 
namespace jLib{
namespace jMath{
namespace jRandom{

extern double jerand48(unsigned short(&xseed)[3]);

}}}