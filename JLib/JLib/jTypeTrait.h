// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/26/2017]
// Description : type traits
#pragma once

#include <type_traits>
#include <iostream>

class Test {
	int a;
	int x, y;
};

template <typename T>
void fun() {
	typedef typename std::is_class<T> type;
	typedef typename std::is_pod<T> type2;
	__fun(type2());
}

void __fun(std::true_type t) {
	std::cout << "Class Type." << std::endl;
}

void __fun(std::false_type t) {
	std::cout << "Not Class Type." << std::endl;
}