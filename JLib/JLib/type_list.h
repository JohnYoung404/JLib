#pragma once
#include <tuple>

namespace mpl
{
	//////////////////////////////////////////////////////////////////////////
	//  usage: mpl::type_list<Args..>::type<N>
	//////////////////////////////////////////////////////////////////////////
	template <class... Args>
	struct type_list
	{
		template <std::size_t N>
		using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
	};
}