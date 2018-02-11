#include "jRandom.h"
#include <mutex>
#include "../extern/rand48/erand48.h"

namespace jLib {
namespace jMath {
namespace jRandom {

int g_index = -1;
std::mutex g_index_mutex;
const int BUFFER_SIZE = 200000;
double* _rand_buffer;
unsigned short _seed[3];

void rand_init()
{
    _rand_buffer = new double[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
        _rand_buffer[i] = erand48(_seed);
    }
}

inline double _jerand48_static_rand()
{
    //std::lock_guard<std::mutex> lock(g_index_mutex);
    g_index = ++g_index >= BUFFER_SIZE ? 0 : g_index;
    return _rand_buffer[g_index];
}

inline double jerand48(unsigned short(&xseed)[3])
{
    //return erand48(xseed);
    return _jerand48_static_rand();
}

}}}