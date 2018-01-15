#pragma once
#include <iostream>


namespace jLib {

struct jITestable
{
	virtual ~jITestable() {}
    virtual void test() {
        std::cout << "testing class: " << typeid(*this).name() << "..." << std::endl;
    };
};

template<size_t N, class T>
void PrintArray(T(&arr)[N]) {
    std::cout << "{ ";
    for (auto i = 0; i < N; ++i)
    {
        std::cout << arr[i] << ", ";
    }
    if (N > 0)
    {
        std::cout << "\b\b" " " "\b";
    }
    std::cout << " }";
}

template <int N>
struct testConstNumber
{
    testConstNumber() { std::cout << N << std::endl; }
};

}

