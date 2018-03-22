#include "jRandom.h"
#include <mutex>
#include "../extern/rand48/erand48.h"

namespace jRayTracing{

namespace {
    class _jRandom_static_holder
    {
    public:
        enum { BUFFER_SIZE = 200000 };
        _jRandom_static_holder()
        {
            g_index = -1;
            _rand_buffer = new jReal[BUFFER_SIZE];
            for (int i = 0; i < BUFFER_SIZE; ++i)
            {
                _rand_buffer[i] = static_cast<float>(erand48(_seed));
            }
        }
        ~_jRandom_static_holder()
        {
            delete[] _rand_buffer;
        }
    public:
        jReal* _rand_buffer;
        int g_index;
        std::mutex g_index_mutex;
        unsigned short _seed[3];
    };

    _jRandom_static_holder _holder;
}

inline jReal _jerand48_static_rand()
{
    //std::lock_guard<std::mutex> lock(_holder.g_index_mutex);
    _holder.g_index = ++_holder.g_index >= _jRandom_static_holder::BUFFER_SIZE ? 0 : _holder.g_index;
    return _holder._rand_buffer[_holder.g_index];
}

inline jReal jerand48(unsigned short(&xseed)[3])
{
    //return erand48(xseed);
    return _jerand48_static_rand();
}

}