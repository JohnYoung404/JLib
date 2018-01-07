#pragma once

#include <vector>

namespace jLib
{

namespace jVectorUtil
{

template <typename Type>
const std::vector<Type> reverse(const std::vector<Type> & prime)
{
    return std::vector<Type>(prime.rbegin(), prime.rend());
}

template <typename Type>
const std::vector<Type> head(const std::vector<Type> & input, size_t num)
{
    return num < input.size() ? std::vector<Type>(input.begin(), input.begin() + num) : input;
}

template <typename Type>
const std::vector<Type> tail(const std::vector<Type> & input, size_t num)
{
    return num < input.size() ? std::vector<Type>(input.begin() + input.size() - num, input.end()) : input;
}

}

}