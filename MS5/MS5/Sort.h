// Milestone:	5
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Sort.h
#ifndef SICT_SORT_H
#define SICT_SORT_H

namespace sict {

	//template <class T, int N>
	//class Array {
	//	T a[N];
	//public:
	//	T& operator[](int i) { return a[i]; }
	//};

	template <class Item>
	void sort(Item a[], size_t size)
	{
		size_t idx, pass;
		for (pass = 1; pass <= size; ++pass)
		{
			for (idx = 0; idx <= size - 2; ++idx)
			{
				if (a[idx] > a[idx + 1])
					swap(a[idx], a[idx + 1]);
			}
		}

	}
}
#endif