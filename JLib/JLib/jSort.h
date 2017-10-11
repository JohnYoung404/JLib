#pragma once

#include "jHeap.h"

namespace jLib {

	template<typename T, size_t N>
	inline void arrayCopy(T(&from)[N], T(&to)[N]) {
		for (int i = 0; i < N; ++i)
		{
			to[i] = from[i];
		}
	}

	class jSort {
	public:
		template <typename T, size_t N>
		static void qsort(T(&arr)[N]);

		template <typename T, size_t N>
		static void heapsort(T(&arr)[N]);

		template <typename T, size_t N>
		static void insertionsort(T(&arr)[N]);

		template <typename T, size_t N>
		static void shellsort(T(&arr)[N]);

		template <typename T, size_t N>
		static void mergesort(T(&arr)[N]);

		template <typename T, size_t N>
		static void countingsort(T(&arr)[N]);

	private:
		template <typename T>
		static void _qsort(T* arr, int p, int q);

		template <typename T>
		static void _mergesort(T* arr, T* tmp, int left, int right);

		template <typename T>
		static int partition(T* arr, int p, int q);

		template <typename T>
		static void merge(T* arr, T* tmp, int Lpos, int Rpos, int Rightend);
	};

	template <typename T>
	static int jSort::partition(T* arr, int p, int q) {
		T x = arr[q];
		int i = p - 1;
		for (int j = p; j < q; ++j)
		{
			if (arr[j] <= x)
			{
				++i;
				swap(arr[i], arr[j]);
			}
		}
		swap(arr[i + 1], arr[q]);
		return i + 1;
	}

	template <typename T, size_t N>
	static void jSort::qsort(T(&arr)[N]) {
		_qsort(arr, 0, N - 1);
	}

	template <typename T>
	static void jSort::_qsort(T* arr, int p, int q) {
		if (p < q)
		{
			int t = partition(arr, p, q);
			_qsort(arr, p, t - 1);
			_qsort(arr, t + 1, q);
		}
	}

	template <typename T, size_t N>
	static void jSort::heapsort(T(&arr)[N]) {
		jLib::heapsort(arr);
	}

	template <typename T, size_t N>
	static void jSort::insertionsort(T(&arr)[N]) {
		int j, p;
		T tmp;
		for (p = 1; p < N; ++p)
		{
			tmp = arr[p];
			for (j = p; j > 0 && arr[j - 1] > tmp; j--)
				arr[j] = arr[j - 1];
			arr[j] = tmp;
		}
	}

	template <typename T, size_t N>
	static void jSort::shellsort(T(&arr)[N]) {
		int j, i, Increment;
		T tmp;
		for (Increment = N / 2; Increment > 0; Increment /= 2)
		{
			for (i = Increment; i < N; ++i)
			{
				tmp = arr[i];
				for (j = i; j >= Increment; j -= Increment)
					if (tmp < arr[j - Increment])
						arr[j] = arr[j - Increment];
					else
						break;
				arr[j] = tmp;
			}
		}
	}

	template <typename T, size_t N>
	static void jSort::mergesort(T(&arr)[N]) {
		T tmpArr[N];
		_mergesort(arr, tmpArr, 0, N - 1);
	}

	template <typename T>
	static void jSort::_mergesort(T* arr, T* tmp, int left, int right) {
		int center;
		if (left < right)
		{
			center = (left + right) / 2;
			_mergesort(arr, tmp, left, center);
			_mergesort(arr, tmp, center + 1, right);
			merge(arr, tmp, left, center + 1, right);
		}
	}

	template <typename T>
	static void jSort::merge(T* arr, T* tmp, int Lpos, int Rpos, int Rightend) {
		int i, Leftend, NumElements, TmpPos;
		Leftend = Rpos - 1;
		TmpPos = Lpos;
		NumElements = Rightend - Lpos + 1;
		while (Lpos <= Leftend && Rpos <= Rightend)
		{
			if (arr[Lpos] <= arr[Rpos])
				tmp[TmpPos++] = arr[Lpos++];
			else
				tmp[TmpPos++] = arr[Rpos++];
		}
		while (Lpos <= Leftend)
		{
			tmp[TmpPos++] = arr[Lpos++];
		}
		while (Rpos <= Rightend)
		{
			tmp[TmpPos++] = arr[Rpos++];
		}
		for (i = 0; i < NumElements; i++, Rightend--)
		{
			arr[Rightend] = tmp[Rightend];
		}
	}

	template <typename T, size_t N>
	static void jSort::countingsort(T(&arr)[N]) {
		int maxVal = 0;
		for (int i = 0; i < N; ++i)
		{
			if (arr[i] > maxVal)	maxVal = arr[i];
		}
		T tmpArr[N];
		T* C = new T[maxVal + 1];
		if (C == NULL)
		{
			throw std::runtime_error("fail to alloc.");
		}
		memset(C, 0, (maxVal + 1) * sizeof(int));
		for (int j = 0; j < N; ++j)
		{
			C[arr[j]] = C[arr[j]] + 1;
		}
		for (int i = 1; i < maxVal + 1; ++i)
		{
			C[i] = C[i] + C[i - 1];
		}
		for (int j = N - 1; j >= 0; j--)
		{
			tmpArr[C[arr[j]] - 1] = arr[j];
			C[arr[j]] = C[arr[j]] - 1;
		}
		arrayCopy(tmpArr, arr);
		delete[] C;
	}

}