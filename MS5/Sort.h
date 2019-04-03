// Milestone:	5
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Sort.h
#ifndef SICT_SORT_H
#define SICT_SORT_H

namespace sict {



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

	//template <class T, int N>
	//class Array {
	//	T a[N];
	//public:
	//	T& operator[](int i) { return a[i]; }
	//};

	template <typename t>
	void asort(t a[], size_t n) {
		size_t i, j, m;
		t temp;

		for (i = 0; i < n; i++) {
			m = i;
			for (j = i + 1; j < n; j++)
				if (a[j] < a[m]) {
					m = j;
				}
			if (m != i) {
				temp = a[i];
				a[i] = a[m];
				a[m] = temp;
			}
		}
	}
}
#endif