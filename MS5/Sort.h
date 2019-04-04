// Milestone:	5
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Sort.h
#ifndef SICT_SORT_H
#define SICT_SORT_H

namespace sict {

	template <typename t>
	void sort(t*a[], size_t n) {
		size_t i, j, m;
		t* temp;

		for (i = 0; i < n; i++) {
			m = i;
			for (j = i + 1; j < n; j++)
				if (*a[m] > *a[j]) {
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