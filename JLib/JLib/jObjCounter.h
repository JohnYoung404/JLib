#pragma once
#include <mutex>
#include "jUtility.h"

//#define  _OPEN_OBJ_COUNTER

NAME_SPACE_BEGIN(jLib)

#ifdef _OPEN_OBJ_COUNTER

template <typename T>
class jObjCounter
{
public:
    jObjCounter()
    {
        std::lock_guard<std::mutex> lock(jObjCounter::_mutex);
        ++_objects_created;
        ++_objects_alive;
    }

    jObjCounter(jObjCounter &&)
    {
        std::lock_guard<std::mutex> lock(jObjCounter::_mutex);
        ++_objects_created;
        ++_objects_alive;
    }

    jObjCounter(const jObjCounter&)
    {
        std::lock_guard<std::mutex> lock(jObjCounter::_mutex);
        ++_objects_created;
        ++_objects_alive;
    }
    static int ObjectCreated() { return _objects_created; }
    static int ObjectAlive() { return _objects_alive; }
protected:
    ~jObjCounter() // objects should never be removed through pointers of this type
    {
        std::lock_guard<std::mutex> lock(jObjCounter::_mutex);
        --_objects_alive;
    }
private:
    static int _objects_created;
    static int _objects_alive;
    static std::mutex _mutex;
};

template <typename T> int jObjCounter<T>::_objects_created(0);
template <typename T> int jObjCounter<T>::_objects_alive(0);
template <typename T> std::mutex jObjCounter<T>::_mutex;

#else

template <typename T>
class jObjCounter
{
public:
    static int ObjectCreated() { return 0; }
    static int ObjectAlive() { return 0; }
};

#endif // _OPEN_OBJ_COUNTER

NAME_SPACE_END