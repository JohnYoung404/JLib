#pragma once

namespace jLib {

	template<typename T>
	void siftup(T* arr, int n) {
		int i = n, p;
		while (1)
		{
			if (i == 1)
			{
				break;
			}
			p = i / 2;
			if (arr[p - 1] <= arr[i - 1]) break;
			swap(arr[p - 1], arr[i - 1]);
			i = p;
		}
	}

	template<typename T>
	void siftdown(T* arr, int n) {
		int i = 1, p;
		while (1)
		{
			p = 2 * i;
			if (p > n) {
				break;
			}
			if (p + 1 <= n) {
				if (arr[p] < arr[p - 1])	p = p + 1;
			}
			if (arr[i - 1] <= arr[p - 1]) break;
			swap(arr[p - 1], arr[i - 1]);
			i = p;
		}
	}

	template<typename T>
	void swap(T &a, T &b) {
		T tmp = std::move(a);
		a = std::move(b);
		b = std::move(tmp);
	}

	template<typename T>
	void heapfy(T* arr, int n) {
		for (int i = 2; i <= n; ++i) {
			siftup(arr, i);
		}
	}

	template<typename T, size_t N>
	void heapsort(T(&arr)[N]) {
		heapfy(arr, N);
		for (int i = N; i >= 2; --i) {
			swap(arr[0], arr[i - 1]);
			siftdown(arr, i - 1);
		}
	}

	template<typename T>
	class jPriQueue
	{
	public:
		jPriQueue(int m)
			: elemNum(0)
			, maxSize(m) {
			arr = new T[maxSize];
		};
		~jPriQueue() {
			delete[] arr;
		}
		void insert(T t) {
			++elemNum;
			if (elemNum > maxSize) throw std::runtime_error("Queue Overflow");
			arr[elemNum - 1] = t;
			siftup(arr, elemNum);
		}
		T extractMin() {
			if (elemNum == 0) throw std::runtime_error("No element in the priority queue.");
			T ret = arr[0];
			arr[0] = arr[elemNum - 1];
			elemNum--;
			siftdown(arr, elemNum);
			return ret;
		}
		inline int size() {
			return elemNum;
		}
	private:
		int elemNum;
		int maxSize;
		T* arr;
	};

	template<typename T, size_t N>
	void putMaxKValueInFront(T(&arr)[N], int K) {	//time complexity : worst case: N * log(K), best case: N
		if (K >= N)
		{
			return;
		}
		else {
			heapfy(arr, K);
			for (int i = K; i < N; ++i)
			{
				if (arr[i] <= arr[0])
				{
					continue;
				}
				else {
					swap(arr[i], arr[0]);
					siftdown(arr, K);
				}
			}
		}
	}

}