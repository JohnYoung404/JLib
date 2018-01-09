#pragma once

#include <vector>
#include <boost/optional.hpp>
#include "jTestBase.h"

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

template <typename Type>
const std::vector<size_t> findAll(const std::vector<Type> & input, const Type& val)
{
	std::vector<size_t> ret;
	for (const auto & v : input)
	{
		if (v == val) ret.push_back(v);
	}
	return ret;
}

template <typename Type>
const bool contains(const std::vector<Type> & input, const Type &val)
{
	for (const auto & v : input)
	{
		if (v == val) return true;
	}
	return false;
}

template <typename Type>
const size_t count(const std::vector<Type> & input, const Type &val)
{
	return findAll(input, val).size();
}

template <typename Type, typename UnaryPredicate>
const std::vector<Type> Where(const std::vector<Type> & input, const UnaryPredicate &pred)
{
	std::vector<Type> ret;
	for (const auto & v : input)
	{
		if (pred(v)) ret.push_back(v);
	}
	return ret;
}

template <typename Type, typename FoldFunction>
const boost::optional<Type> foldL(const std::vector<Type> & input, const FoldFunction &folder)
{
	if (input.size() == 0) return boost::none;
	Type ret = input[0];
	for (size_t i = 1; i < input.size(); ++i)
	{
		ret = folder(ret, input[i]);
	}
	return ret;
}

}

}