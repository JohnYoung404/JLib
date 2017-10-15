#pragma once
#include <iostream>
#include "jMPL.h"

struct jITestable
{
    virtual void test() {
        std::cout << std::endl << "testing class: " << typeid(*this).name() << "..." << std::endl;
    };
};

template<size_t N, class T>
void PrintArray(T (&arr)[N]) {
    std::cout << "{";
    for (auto i = 0; i < N; ++i)
    {
        std::cout << arr[i] << ", ";
    }
    if (N > 0)
    {
        std::cout << "\b\b" " " "\b";
    }
    std::cout << "}";
}