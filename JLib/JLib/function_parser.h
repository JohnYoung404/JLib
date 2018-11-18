#pragma once
#include <functional>
#include <boost/function.hpp>
#include "type_list.h"

namespace util
{
	template<typename T>
	struct function_parser;

	template<typename R, typename... Args >
	struct function_parser<R(Args...)>
	{
		using return_type = R;
		enum { arg_count = sizeof...(Args) };

		template<std::size_t N>
		struct arg
		{
			using type = typename argsList::type<N>;
		};
	private:
		using argsList = mpl::type_list<Args...>;
	};

//////////////////////////////////////////////////////////////////////////

#define RegisterFuncType(FuncType) template<typename R, typename... Args > \
		struct function_parser<FuncType>{ \
		using return_type = R; \
		enum { arg_count = sizeof...(Args) };\
		template<std::size_t N> \
		struct arg { using type = typename argsList::type<N>; }; \
		private: \
		using argsList = mpl::type_list<Args...>;};

#define RegisterMemberFuncType(FuncType) template<typename R, typename T, typename... Args > \
		struct function_parser<FuncType>{ \
		using return_type = R; \
		enum { arg_count = sizeof...(Args) };\
		template<std::size_t N> \
		struct arg { using type = typename argsList::type<N>; }; \
		private: \
		using argsList = mpl::type_list<Args...>;};

	//non-member function template specifications
	RegisterFuncType(R(*)(Args...))
	RegisterFuncType(std::function<R(Args...)>)
	RegisterFuncType(boost::function<R(Args...)>)

	//class member function template specifications
	RegisterMemberFuncType(R(T::*)(Args...))
	RegisterMemberFuncType(R(T::*)(Args...) const)
	RegisterMemberFuncType(R(T::*)(Args...) volatile)
	RegisterMemberFuncType(R(T::*)(Args...) const volatile)
}